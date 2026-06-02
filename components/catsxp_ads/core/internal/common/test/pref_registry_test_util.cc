/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/pref_registry_test_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/local_state_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"
#include "components/variations/pref_names.h"

namespace catsxp_ads::test {

void RegisterLocalStatePrefs() {
  // Ads prefs.
  RegisterLocalStateTimePref(prefs::kFirstRunAt, DistantPast());

  // Variations prefs.
  RegisterLocalStateStringPref(variations::prefs::kVariationsCountry, "US");
}

void RegisterProfilePrefs() {
  // Ads prefs.
  RegisterProfileTimeDeltaPref(prefs::kGracePeriod, base::Days(3));

  RegisterProfileStringPref(prefs::kDiagnosticId, "");

  RegisterProfileBooleanPref(prefs::kOptedInToNotificationAds, true);
  RegisterProfileInt64Pref(prefs::kMaximumNotificationAdsPerHour, -1);

  RegisterProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);

  RegisterProfileBooleanPref(prefs::kShouldAllowSubdivisionTargeting, false);
  RegisterProfileStringPref(prefs::kSubdivisionTargetingUserSelectedSubdivision,
                            "AUTO");
  RegisterProfileStringPref(prefs::kSubdivisionTargetingAutoDetectedSubdivision,
                            "");

  RegisterProfileStringPref(prefs::kCatalogId, "");
  RegisterProfileIntegerPref(prefs::kCatalogVersion, 0);
  RegisterProfileInt64Pref(prefs::kCatalogPing, 7'200'000);
  RegisterProfileTimePref(prefs::kCatalogLastUpdated, base::Time());

  RegisterProfileIntegerPref(prefs::kIssuerPing, 0);
  RegisterProfileListPref(prefs::kIssuers);

  RegisterProfileListPref(prefs::kNotificationAds);
  RegisterProfileTimePref(prefs::kServeAdAt, Now());

  RegisterProfileTimePref(prefs::kNextPaymentTokenRedemptionAt,
                          DistantFuture());

  RegisterProfileDictPref(prefs::kAdReactions);
  RegisterProfileDictPref(prefs::kSegmentReactions);
  RegisterProfileListPref(prefs::kSaveAds);
  RegisterProfileListPref(prefs::kMarkedAsInappropriate);

  RegisterProfileBooleanPref(prefs::kHasMigratedClientState, true);

  RegisterProfileStringPref(prefs::kBrowserVersionNumber, "");

  // Rewards prefs.
  RegisterProfileBooleanPref(catsxp_rewards::prefs::kEnabled, true);
  RegisterProfileBooleanPref(catsxp_rewards::prefs::kDisabledByPolicy, false);
  RegisterProfileStringPref(catsxp_rewards::prefs::kExternalWalletType,
                            "connected");

  // New tab page background image prefs.
  RegisterProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, true);
  RegisterProfileBooleanPref(ntp_background_images::prefs::
                                 kNewTabPageShowSponsoredImagesBackgroundImage,
                             true);
  RegisterProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist,
      true);
}

}  // namespace catsxp_ads::test
