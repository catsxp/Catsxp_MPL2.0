/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ROUND_ROBIN_CREATIVE_AD_ROUND_ROBIN_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ROUND_ROBIN_CREATIVE_AD_ROUND_ROBIN_H_

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "base/containers/flat_set.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/eligible_ads_feature.h"

namespace catsxp_ads {

// Ensures every ad is served once per rotation before any repeats, and prevents
// the most recently served ad from being the first served in the next rotation
// when possible. State is intentionally kept in memory only and not persisted.
class CreativeAdRoundRobin final {
 public:
  CreativeAdRoundRobin();

  CreativeAdRoundRobin(const CreativeAdRoundRobin&) = delete;
  CreativeAdRoundRobin& operator=(const CreativeAdRoundRobin&) = delete;

  ~CreativeAdRoundRobin();

  // Filters out served `creative_ads`, resetting the rotation when all
  // creatives in the current set have been served. On reset, excludes the last
  // served creative to avoid an immediate repeat unless it would leave no ads
  // to serve.
  template <typename T>
  void Filter(std::vector<T>& creative_ads) {
    if (!kShouldRoundRobin.Get()) {
      return;
    }

    if (creative_ads.empty()) {
      // Filtering an empty ad list indicates that no campaigns are active, so
      // the round-robin state should reset.
      served_creative_instance_ids_.clear();
      return;
    }

    // Check if all creative ads have been served.
    if (std::ranges::all_of(creative_ads, [this](const T& creative_ad) {
          return served_creative_instance_ids_.contains(
              creative_ad.creative_instance_id);
        })) {
      // All ads have been served, so reset for the next round, including any
      // creative instance IDs from removed campaigns.
      served_creative_instance_ids_.clear();

      if (last_served_creative_instance_id_ && creative_ads.size() > 1) {
        // Exclude the last served creative ad to avoid an immediate repeat if
        // there is more than one creative ad.
        served_creative_instance_ids_.insert(
            *last_served_creative_instance_id_);
      }
    }

    // Remove served ads from the eligible ads for this serving round.
    std::erase_if(creative_ads, [this](const T& creative_ad) {
      return served_creative_instance_ids_.contains(
          creative_ad.creative_instance_id);
    });
  }

  // Marks a creative ad as served to avoid repeats within a rotation.
  template <typename T>
  void MarkAsServed(const T& creative_ad) {
    if (!kShouldRoundRobin.Get()) {
      return;
    }

    served_creative_instance_ids_.insert(creative_ad.creative_instance_id);
    last_served_creative_instance_id_ = creative_ad.creative_instance_id;
  }

 private:
  base::flat_set<std::string> served_creative_instance_ids_;
  std::optional<std::string> last_served_creative_instance_id_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ROUND_ROBIN_CREATIVE_AD_ROUND_ROBIN_H_
