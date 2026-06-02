/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/search_result_ads/search_result_ad_event_handler_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_handler_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

void MaybeBuildAndSaveCreativeSetConversion(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad,
    mojom::SearchResultAdEventType mojom_ad_event_type) {
  const bool user_has_joined_rewards = UserHasJoinedCatsxpRewards();

  // Save only if:
  // - User has joined Catsxp Rewards and a viewed impression event was fired.
  // - User has not joined Catsxp Rewards and a clicked impression event was
  //   fired.

  const bool fired_view_event_for_rewards_user =
      user_has_joined_rewards &&
      mojom_ad_event_type == mojom::SearchResultAdEventType::kViewedImpression;

  const bool fired_click_event_for_non_rewards_user =
      !user_has_joined_rewards &&
      mojom_ad_event_type == mojom::SearchResultAdEventType::kClicked;

  const bool should_save = fired_view_event_for_rewards_user ||
                           fired_click_event_for_non_rewards_user;
  if (!should_save) {
    // Do not save if the event type is not supported.
    return;
  }

  if (std::optional<CreativeSetConversionInfo> creative_set_conversion =
          FromMojomMaybeBuildCreativeSetConversion(mojom_creative_ad)) {
    database::SaveCreativeSetConversions({*creative_set_conversion});
  }
}

bool IsAllowedToFireAdEvent(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad,
    mojom::SearchResultAdEventType mojom_ad_event_type) {
  CHECK(mojom_creative_ad);

  if (UserHasJoinedCatsxpRewards()) {
    // Always allowed to fire events for Rewards users.
    return true;
  }

  if (mojom_ad_event_type != mojom::SearchResultAdEventType::kClicked) {
    // Not allowed to fire events other than clicked for non-Rewards users.
    return false;
  }

  if (!mojom_creative_ad->creative_set_conversion) {
    // Not allowed if there is no creative set conversion for non-Rewards users.
    return false;
  }

  return true;
}

bool ShouldFireAdEvent(const SearchResultAdInfo& ad,
                       const AdEventList& ad_events,
                       mojom::SearchResultAdEventType mojom_ad_event_type) {
  if (UserHasJoinedCatsxpRewards() &&
      !WasAdServed(ad, ad_events, mojom_ad_event_type)) {
    BLOG(1,
         "Search result ad: Not allowed because an ad was not served for "
         "placement id "
             << ad.placement_id);
    return false;
  }

  if (ShouldDeduplicateAdEvent(ad, ad_events, mojom_ad_event_type)) {
    BLOG(1, "Search result ad: Not allowed as deduplicated "
                << mojom_ad_event_type << " event for placement id "
                << ad.placement_id);
    return false;
  }

  return true;
}

}  // namespace catsxp_ads
