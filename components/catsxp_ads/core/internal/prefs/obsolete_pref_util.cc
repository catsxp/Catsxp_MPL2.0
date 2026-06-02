/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/prefs/obsolete_pref_util.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kObsoleteShouldShowSearchResultAdClickedInfoBar =
    "catsxp.catsxp_ads.should_show_search_result_ad_clicked_infobar";

constexpr std::string_view kObsoleteHasMigratedConfirmationStateV8 =
    "catsxp.catsxp_ads.state.has_migrated.confirmations.v8";
constexpr std::string_view kObsoleteHasMigratedStateV2 =
    "catsxp.catsxp_ads.state.has_migrated.v2";

constexpr std::string_view kObsoleteNotificationAdLastNormalizedCoordinateX =
    "catsxp.catsxp_ads.ad_notification.last_normalized_coordinate_x";
constexpr std::string_view kObsoleteNotificationAdLastNormalizedCoordinateY =
    "catsxp.catsxp_ads.ad_notification.last_normalized_coordinate_y";
constexpr std::string_view kObsoleteNotificationAdDidFallbackToCustom =
    "catsxp.catsxp_ads.ad_notification.did_fallback_to_custom";

constexpr const char* kObsoleteP2APrefPaths[] = {
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.architecture)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.artsentertainment)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.automotive)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.business)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.careers)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.cellphones)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.crypto)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.education)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.familyparenting)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.fashion)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.folklore)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.fooddrink)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.gaming)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.healthfitness)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.history)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.hobbiesinterests)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.home)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.law)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.military)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.other)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.personalfinance)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.pets)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.realestate)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.science)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.sports)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.technologycomputing)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.travel)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.untargeted)",
    R"(catsxp.weekly_storage.Catsxp.P2A.ad_notification.opportunities_per_segment.weather)",
    R"(catsxp.weekly_storage.Catsxp.P2A.inline_content_ad.opportunities)",
    R"(catsxp.weekly_storage.Catsxp.P2A.new_tab_page_ad.opportunities)"};

constexpr std::string_view kNewTabPageEventCountDictPref =
    "catsxp.catsxp_ads.p3a.ntp_event_count";
constexpr std::string_view kNewTabPageEventCountConstellationDictPref =
    "catsxp.catsxp_ads.p3a.ntp_event_count_constellation";
constexpr std::string_view kNewTabPageKnownCampaignsDictPref =
    "catsxp.catsxp_ads.p3a.ntp_known_campaigns";

void MaybeMigrateShouldShowSearchResultAdClickedInfoBarProfilePref(
    PrefService* const prefs) {
  if (!prefs->HasPrefPath(kObsoleteShouldShowSearchResultAdClickedInfoBar)) {
    return;
  }

  prefs->SetBoolean(
      prefs::kShouldShowSearchResultAdClickedInfoBar,
      prefs->GetBoolean(kObsoleteShouldShowSearchResultAdClickedInfoBar));
  prefs->ClearPref(kObsoleteShouldShowSearchResultAdClickedInfoBar);
}

}  // namespace

void RegisterProfilePrefsForMigration(PrefRegistrySimple* const registry) {
  // Added 05/2025.
  registry->RegisterBooleanPref(kObsoleteShouldShowSearchResultAdClickedInfoBar,
                                false);

  // Added 06/2025.
  for (const auto* path : kObsoleteP2APrefPaths) {
    registry->RegisterListPref(path);
  }

  // Added 03/2026.
  registry->RegisterDoublePref(kObsoleteNotificationAdLastNormalizedCoordinateX,
                               0.0);
  registry->RegisterDoublePref(kObsoleteNotificationAdLastNormalizedCoordinateY,
                               0.0);
  registry->RegisterBooleanPref(kObsoleteNotificationAdDidFallbackToCustom,
                                false);

  // Added 04/2026.
  registry->RegisterBooleanPref(kObsoleteHasMigratedConfirmationStateV8, false);
  registry->RegisterBooleanPref(kObsoleteHasMigratedStateV2, false);
}

void MigrateObsoleteProfilePrefs(PrefService* const prefs) {
  // Added 05/2025.
  MaybeMigrateShouldShowSearchResultAdClickedInfoBarProfilePref(prefs);

  // Added 06/2025.
  for (const auto* path : kObsoleteP2APrefPaths) {
    prefs->ClearPref(path);
  }

  // Added 03/2026.
  prefs->ClearPref(kObsoleteNotificationAdLastNormalizedCoordinateX);
  prefs->ClearPref(kObsoleteNotificationAdLastNormalizedCoordinateY);
  prefs->ClearPref(kObsoleteNotificationAdDidFallbackToCustom);

  // Added 04/2026.
  prefs->ClearPref(kObsoleteHasMigratedConfirmationStateV8);
  prefs->ClearPref(kObsoleteHasMigratedStateV2);
}

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry) {
  // Added 06/2025
  registry->RegisterDictionaryPref(kNewTabPageEventCountDictPref);

  // Added 10/2025
  registry->RegisterDictionaryPref(kNewTabPageEventCountConstellationDictPref);
  registry->RegisterDictionaryPref(kNewTabPageKnownCampaignsDictPref);
}

void MigrateObsoleteLocalStatePrefs(PrefService* local_state) {
  // Added 06/2025
  local_state->ClearPref(kNewTabPageEventCountDictPref);

  // Added 10/2025
  local_state->ClearPref(kNewTabPageEventCountConstellationDictPref);
  local_state->ClearPref(kNewTabPageKnownCampaignsDictPref);
}

}  // namespace catsxp_ads
