/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads::prefs {

// IMPORTANT: Prefs that need clearing should be prefixed with
// `catsxp.catsxp_ads`.

// Ads prefs.
inline constexpr char kFirstRunAt[] = "catsxp.catsxp_ads.first_run_at";

inline constexpr char kGracePeriod[] = "catsxp.catsxp_ads.grace_period";

inline constexpr char kDiagnosticId[] = "catsxp.catsxp_ads.diagnostics.id";

inline constexpr char kOptedInToNotificationAds[] = "catsxp.catsxp_ads.enabled";
inline constexpr char kMaximumNotificationAdsPerHour[] =
    "catsxp.catsxp_ads.ads_per_hour";

inline constexpr char kOptedInToSearchResultAds[] =
    "catsxp.catsxp_ads.opted_in_to_search_result_ads";

inline constexpr char kShouldAllowSubdivisionTargeting[] =
    "catsxp.catsxp_ads.should_allow_ads_subdivision_targeting";
inline constexpr char kSubdivisionTargetingUserSelectedSubdivision[] =
    "catsxp.catsxp_ads.ads_subdivision_targeting_code";
inline constexpr char kSubdivisionTargetingAutoDetectedSubdivision[] =
    "catsxp.catsxp_ads.automatically_detected_ads_subdivision_targeting_code";

inline constexpr char kCatalogId[] = "catsxp.catsxp_ads.catalog_id";
inline constexpr char kCatalogVersion[] = "catsxp.catsxp_ads.catalog_version";
inline constexpr char kCatalogPing[] = "catsxp.catsxp_ads.catalog_ping";
inline constexpr char kCatalogLastUpdated[] =
    "catsxp.catsxp_ads.catalog_last_updated";

inline constexpr char kIssuerPing[] = "catsxp.catsxp_ads.issuer_ping";
inline constexpr char kIssuers[] = "catsxp.catsxp_ads.issuers";

inline constexpr char kNotificationAds[] = "catsxp.catsxp_ads.notification_ads";
inline constexpr char kServeAdAt[] = "catsxp.catsxp_ads.serve_ad_at";

inline constexpr char kNextPaymentTokenRedemptionAt[] =
    "catsxp.catsxp_ads.rewards.next_time_redemption_at";

inline constexpr char kAdReactions[] = "catsxp.catsxp_ads.reactions.ads";
inline constexpr char kSegmentReactions[] =
    "catsxp.catsxp_ads.reactions.segments";
inline constexpr char kSaveAds[] = "catsxp.catsxp_ads.reactions.saved_ads";
inline constexpr char kMarkedAsInappropriate[] =
    "catsxp.catsxp_ads.reactions.marked_as_inappropriate";

inline constexpr char kHasMigratedClientState[] =
    "catsxp.catsxp_ads.state.has_migrated.client.v7";
inline constexpr char kBrowserVersionNumber[] =
    "catsxp.catsxp_ads.browser_version_number";

// Ads service prefs.
inline constexpr char kShouldShowOnboardingNotification[] =
    "catsxp.catsxp_ads.should_show_my_first_ad_notification";

// Catsxp stats prefs.
inline constexpr char kEnabledForLastProfile[] =
    "catsxp.catsxp_ads.enabled_last_profile";
inline constexpr char kEverEnabledForAnyProfile[] =
    "catsxp.catsxp_ads.ever_enabled_any_profile";

// OHTTP prefs.
inline constexpr char kObliviousHttpKeyConfig[] =
    "catsxp.catsxp_ads.ohttp.key_config.public_key";
inline constexpr char kObliviousHttpKeyConfigExpiresAt[] =
    "catsxp.catsxp_ads.ohttp.key_config.expires_at";

// We don't prefix `catsxp.catsxp_ads` to this pref path because we don't want
// them cleared if the user clears ads data or resets Catsxp Rewards.
inline constexpr char kShouldShowSearchResultAdClickedInfoBar[] =
    "catsxp.search.search_result_ad.should_show_clicked_infobar";

}  // namespace catsxp_ads::prefs

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_
