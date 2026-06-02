/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/prefs/pref_registry.h"

#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace catsxp_ads {

namespace {
constexpr int kDefaultIssuerPingMilliseconds = 7'200'000;
}  // namespace

void RegisterLocalStatePrefs(PrefRegistrySimple* const registry) {
  // Ads prefs.
  registry->RegisterTimePref(prefs::kFirstRunAt, base::Time::Now());

  // Ads service prefs.
  registry->RegisterStringPref(prefs::kObliviousHttpKeyConfig, "");
  registry->RegisterTimePref(prefs::kObliviousHttpKeyConfigExpiresAt,
                             base::Time());
}

void RegisterProfilePrefs(PrefRegistrySimple* const registry) {
  // Ads prefs.
  registry->RegisterTimeDeltaPref(prefs::kGracePeriod, base::Days(3));

  registry->RegisterStringPref(prefs::kDiagnosticId, "");

  registry->RegisterBooleanPref(prefs::kOptedInToNotificationAds, false);
  registry->RegisterInt64Pref(prefs::kMaximumNotificationAdsPerHour, -1);

  registry->RegisterBooleanPref(prefs::kOptedInToSearchResultAds, true);

  registry->RegisterBooleanPref(prefs::kShouldAllowSubdivisionTargeting, false);
  registry->RegisterStringPref(
      prefs::kSubdivisionTargetingUserSelectedSubdivision, "AUTO");
  registry->RegisterStringPref(
      prefs::kSubdivisionTargetingAutoDetectedSubdivision, "");

  registry->RegisterStringPref(prefs::kCatalogId, "");
  registry->RegisterIntegerPref(prefs::kCatalogVersion, 0);
  registry->RegisterInt64Pref(prefs::kCatalogPing, 0);
  registry->RegisterTimePref(prefs::kCatalogLastUpdated, base::Time());

  registry->RegisterIntegerPref(prefs::kIssuerPing,
                                kDefaultIssuerPingMilliseconds);
  registry->RegisterListPref(prefs::kIssuers);

  registry->RegisterListPref(prefs::kNotificationAds);
  registry->RegisterTimePref(prefs::kServeAdAt, base::Time());

  registry->RegisterTimePref(prefs::kNextPaymentTokenRedemptionAt,
                             base::Time::Now());

  registry->RegisterDictionaryPref(prefs::kAdReactions);
  registry->RegisterDictionaryPref(prefs::kSegmentReactions);
  registry->RegisterListPref(prefs::kSaveAds);
  registry->RegisterListPref(prefs::kMarkedAsInappropriate);

  registry->RegisterBooleanPref(prefs::kHasMigratedClientState, false);

  registry->RegisterStringPref(prefs::kBrowserVersionNumber, "");

  // Ads service prefs.
  registry->RegisterBooleanPref(prefs::kShouldShowOnboardingNotification, true);

  registry->RegisterBooleanPref(prefs::kShouldShowSearchResultAdClickedInfoBar,
                                true);
}

}  // namespace catsxp_ads
