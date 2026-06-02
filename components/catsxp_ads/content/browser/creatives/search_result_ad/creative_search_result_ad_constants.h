/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CONSTANTS_H_

namespace catsxp_ads {

inline constexpr char kCreativeSearchResultAdsProductMojomEntityType[] =
    "Product";

inline constexpr char kCreativeSearchResultAdsMojomPropertyName[] = "creatives";

inline constexpr char kCreativeSearchResultAdMojomEntityType[] =
    "SearchResultAd";

// Creative ad.
inline constexpr char kCreativeAdPlacementIdPropertyName[] =
    "data-placement-id";
inline constexpr char kCreativeAdCreativeInstanceIdPropertyName[] =
    "data-creative-instance-id";
inline constexpr char kCreativeAdCreativeSetIdPropertyName[] =
    "data-creative-set-id";
inline constexpr char kCreativeAdCampaignIdPropertyName[] = "data-campaign-id";
inline constexpr char kCreativeAdAdvertiserIdPropertyName[] =
    "data-advertiser-id";
inline constexpr char kCreativeAdLandingPagePropertyName[] =
    "data-landing-page";
inline constexpr char kCreativeAdHeadlineTextPropertyName[] =
    "data-headline-text";
inline constexpr char kCreativeAdDescriptionPropertyName[] = "data-description";
inline constexpr char kCreativeAdRewardsValuePropertyName[] =
    "data-rewards-value";

// Creative set conversion.
inline constexpr char kCreativeSetConversionUrlPatternPropertyName[] =
    "data-conversion-url-pattern-value";
inline constexpr char kCreativeSetConversionObservationWindowPropertyName[] =
    "data-conversion-observation-window-value";

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_CONSTANTS_H_
