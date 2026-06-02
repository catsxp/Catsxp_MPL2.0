/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_TEST_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_TEST_CONSTANTS_H_

#include "base/time/time.h"

namespace catsxp_ads::test {

// Creative ad.
inline constexpr char kCreativeAdPlacementId[] =
    "953f362e-98cd-4fa6-8403-e886185b88fc";
inline constexpr char kCreativeAdPlacementIdWithUnreservedCharacters[] =
    "\"'+*&%";
inline constexpr char kEscapedCreativeAdPlacementIdWithUnreservedCharacters[] =
    "%22%27%2B%2A%26%25";
inline constexpr char kCreativeAdCreativeInstanceId[] =
    "d94f98e6-74f8-41cf-bfb2-3d753b94f8ef";
inline constexpr char kCreativeAdCreativeSetId[] =
    "1b3d1717-372b-4dfc-9aa5-f92cb3ac87ac";
inline constexpr char kCreativeAdCampaignId[] =
    "c2096fe1-3eb7-4096-8fca-04bca89eab35";
inline constexpr char kCreativeAdAdvertiserId[] =
    "c7bf8cbe-01bf-48a8-8282-57b5165c986a";
inline constexpr char kCreativeAdLandingPage[] = "https://catsxp.com";
inline constexpr char kCreativeAdHeadlineText[] = "Headline text";
inline constexpr char kCreativeAdDescription[] = "Description";
inline constexpr double kCreativeAdRewardsValue = 0.5;

// Creative set conversion.
inline constexpr char kCreativeSetConversionUrlPattern[] =
    "https://catsxp.com/*";
inline constexpr base::TimeDelta kCreativeSetConversionObservationWindow =
    base::Days(1);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_TEST_CONSTANTS_H_
