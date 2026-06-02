/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_CREATIVE_AD_CACHE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_CREATIVE_AD_CACHE_H_

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

class TabManager;

using CreativeAdVariant = std::variant<mojom::CreativeSearchResultAdInfoPtr>;
using CreativeAdVariantMap =
    std::map</*placement_id*/ std::string, CreativeAdVariant>;

using PlacementIdList = std::vector<std::string>;
using PlacementIdMap = std::map</*tab_id*/ int32_t, PlacementIdList>;

class CreativeAdCache final : public TabManagerObserver {
 public:
  CreativeAdCache();

  CreativeAdCache(const CreativeAdCache&) = delete;
  const CreativeAdCache& operator=(const CreativeAdCache&) = delete;

  CreativeAdCache(CreativeAdCache&&) = delete;
  const CreativeAdCache& operator=(CreativeAdCache&&) = delete;

  ~CreativeAdCache() override;

  // Adds a creative ad to the cache for the given `placement_id` if it is valid
  // and there is a visible tab.
  void MaybeAdd(const std::string& placement_id,
                CreativeAdVariant creative_ad_variant);

  // Gets a creative ad from the cache if it exists for the given
  // `placement_id`.
  template <typename T>
  std::optional<T> MaybeGet(const std::string& placement_id) {
    std::optional<CreativeAdVariant> creative_ad_variant =
        MaybeGetCreativeAdVariant(placement_id);
    if (!creative_ad_variant) {
      return std::nullopt;
    }

    if (!std::holds_alternative<T>(*creative_ad_variant)) {
      return std::nullopt;
    }

    return std::move(std::get<T>(*creative_ad_variant));
  }

 private:
  std::optional<CreativeAdVariant> MaybeGetCreativeAdVariant(
      const std::string& placement_id) const;

  void PurgePlacements(int32_t tab_id);

  // TabManagerObserver:
  void OnDidCloseTab(int32_t tab_id) override;

  base::ScopedObservation<TabManager, TabManagerObserver>
      tab_manager_observation_{this};

  CreativeAdVariantMap creative_ad_variants_;
  PlacementIdMap placement_ids_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_CREATIVE_AD_CACHE_H_
