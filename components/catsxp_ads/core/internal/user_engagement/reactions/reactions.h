/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_H_

#include <map>
#include <set>
#include <string>

#include "base/observer_list.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_observer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

// `id` can be either `advertiser_id` for liking/disliking an ad or `segment`
// for liking/disliking a segment.
using ReactionMap = std::map</*id*/ std::string, mojom::ReactionType>;

// `id` can be either `creative_instance_id` for saving an ad or
// `creative_set_id` for marking an ad as inappropriate.
using ReactionSet = std::set</*id*/ std::string>;

class Reactions final {
 public:
  Reactions();

  Reactions(const Reactions&) = delete;
  Reactions& operator=(const Reactions&) = delete;

  ~Reactions();

  void AddObserver(ReactionsObserver* observer);
  void RemoveObserver(ReactionsObserver* observer);

  void ToggleLikeAd(mojom::ReactionInfoPtr mojom_reaction,
                    ResultCallback callback);
  void ToggleDislikeAd(mojom::ReactionInfoPtr mojom_reaction,
                       ResultCallback callback);
  mojom::ReactionType AdReactionTypeForId(
      const std::string& advertiser_id) const;
  const ReactionMap& Ads() const { return ad_reactions_; }
  ReactionMap& AdsForTesting() { return ad_reactions_; }

  void ToggleLikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                         ResultCallback callback);
  void ToggleDislikeSegment(mojom::ReactionInfoPtr mojom_reaction,
                            ResultCallback callback);
  mojom::ReactionType SegmentReactionTypeForId(
      const std::string& segment) const;
  const ReactionMap& Segments() const { return segment_reactions_; }
  ReactionMap& SegmentsForTesting() { return segment_reactions_; }

  void ToggleSaveAd(mojom::ReactionInfoPtr mojom_reaction,
                    ResultCallback callback);
  bool IsAdSaved(const std::string& creative_instance_id) const;
  ReactionSet& SavedAdsForTesting() { return saved_ads_; }

  void ToggleMarkAdAsInappropriate(mojom::ReactionInfoPtr mojom_reaction,
                                   ResultCallback callback);
  bool IsAdMarkedAsInappropriate(const std::string& creative_set_id) const;
  ReactionSet& MarkedAdsAsInappropriateForTesting() {
    return marked_as_inappropriate_;
  }

 private:
  void LoadAdReactions();
  void LoadSegmentReactions();
  void LoadSavedAds();
  void LoadMarkedAsInappropriate();
  void Load();

  void NotifyDidLikeAd(const std::string& advertiser_id);
  void NotifyDidDislikeAd(const std::string& advertiser_id);
  void NotifyDidLikeSegment(const std::string& segment);
  void NotifyDidDislikeSegment(const std::string& segment);
  void NotifyDidToggleSaveAd(const std::string& creative_instance_id);
  void NotifyDidToggleMarkAdAsInappropriate(const std::string& creative_set);

  ReactionMap ad_reactions_;
  ReactionMap segment_reactions_;
  ReactionSet saved_ads_;
  ReactionSet marked_as_inappropriate_;

  base::ObserverList<ReactionsObserver> observers_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_H_
