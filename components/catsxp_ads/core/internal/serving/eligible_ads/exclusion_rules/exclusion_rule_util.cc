/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/eligible_ads/exclusion_rules/exclusion_rule_util.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/algorithm/count_if_until_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/creative_ad_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

bool ShouldAlwaysRespectCap(base::TimeDelta time_constraint, size_t cap) {
  return time_constraint.is_zero() || cap == 0;
}

}  // namespace

bool DoesRespectCampaignCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            base::TimeDelta time_constraint,
                            size_t cap) {
  if (ShouldAlwaysRespectCap(time_constraint, cap)) {
    return true;
  }

  const base::Time now = base::Time::Now();

  const size_t count = count_if_until(
      ad_events,
      [&creative_ad, mojom_confirmation_type, now,
       time_constraint](const AdEventInfo& ad_event) {
        CHECK(ad_event.created_at);

        return ad_event.confirmation_type == mojom_confirmation_type &&
               ad_event.campaign_id == creative_ad.campaign_id &&
               now - *ad_event.created_at < time_constraint;
      },
      cap);

  return count < cap;
}

bool DoesRespectCampaignCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            size_t cap) {
  return DoesRespectCampaignCap(creative_ad, ad_events, mojom_confirmation_type,
                                base::TimeDelta::FiniteMax(), cap);
}

bool DoesRespectCreativeSetCap(const CreativeAdInfo& creative_ad,
                               const AdEventList& ad_events,
                               mojom::ConfirmationType mojom_confirmation_type,
                               base::TimeDelta time_constraint,
                               size_t cap) {
  if (ShouldAlwaysRespectCap(time_constraint, cap)) {
    return true;
  }

  const base::Time now = base::Time::Now();

  const size_t count = count_if_until(
      ad_events,
      [&creative_ad, mojom_confirmation_type, now,
       time_constraint](const AdEventInfo& ad_event) {
        CHECK(ad_event.created_at);

        return ad_event.confirmation_type == mojom_confirmation_type &&
               ad_event.creative_set_id == creative_ad.creative_set_id &&
               now - *ad_event.created_at < time_constraint;
      },
      cap);

  return count < cap;
}

bool DoesRespectCreativeSetCap(const CreativeAdInfo& creative_ad,
                               const AdEventList& ad_events,
                               mojom::ConfirmationType mojom_confirmation_type,
                               size_t cap) {
  return DoesRespectCreativeSetCap(creative_ad, ad_events,
                                   mojom_confirmation_type,
                                   base::TimeDelta::FiniteMax(), cap);
}

bool DoesRespectCreativeCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            base::TimeDelta time_constraint,
                            size_t cap) {
  if (ShouldAlwaysRespectCap(time_constraint, cap)) {
    return true;
  }

  const base::Time now = base::Time::Now();

  const size_t count = count_if_until(
      ad_events,
      [&creative_ad, mojom_confirmation_type, now,
       time_constraint](const AdEventInfo& ad_event) {
        CHECK(ad_event.created_at);

        return ad_event.confirmation_type == mojom_confirmation_type &&
               ad_event.creative_instance_id ==
                   creative_ad.creative_instance_id &&
               now - *ad_event.created_at < time_constraint;
      },
      cap);

  return count < cap;
}

bool DoesRespectCreativeCap(const CreativeAdInfo& creative_ad,
                            const AdEventList& ad_events,
                            mojom::ConfirmationType mojom_confirmation_type,
                            size_t cap) {
  return DoesRespectCreativeCap(creative_ad, ad_events, mojom_confirmation_type,
                                base::TimeDelta::FiniteMax(), cap);
}

}  // namespace catsxp_ads
