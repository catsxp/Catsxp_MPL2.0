/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_

#include <cstdint>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "build/build_config.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

inline constexpr char kNotificationAdTypeKey[] = "type";
inline constexpr char kNotificationAdPlacementIdKey[] = "uuid";
inline constexpr char kNotificationAdCreativeInstanceIdKey[] =
    "creative_instance_id";
inline constexpr char kNotificationAdCreativeSetIdKey[] = "creative_set_id";
inline constexpr char kNotificationAdCampaignIdKey[] = "campaign_id";
inline constexpr char kNotificationAdAdvertiserIdKey[] = "advertiser_id";
inline constexpr char kNotificationAdSegmentKey[] = "segment";
inline constexpr char kNotificationAdTitleKey[] = "title";
inline constexpr char kNotificationAdBodyKey[] = "body";
inline constexpr char kNotificationAdTargetUrlKey[] = "target_url";

// Catsxp Ads per hour are user configurable within the catsxp://rewards ads UI.
#if !BUILDFLAG(IS_IOS)
inline constexpr int64_t kDefaultCatsxpRewardsNotificationAdsPerHour = 10;
#else
inline constexpr int64_t kDefaultCatsxpRewardsNotificationAdsPerHour = 2;
#endif  // !BUILDFLAG(IS_IOS)

// Default ad notification timeout in seconds.
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)
inline constexpr base::TimeDelta kDefaultNotificationAdTimeout =
    base::Minutes(2);
#else
inline constexpr base::TimeDelta kDefaultNotificationAdTimeout =
    base::Seconds(30);
#endif  // !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_IOS)


}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NOTIFICATION_AD_NOTIFICATION_AD_CONSTANTS_H_
