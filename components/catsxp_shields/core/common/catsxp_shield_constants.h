/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_CONSTANTS_H_

#include "base/containers/fixed_flat_map.h"
#include "base/containers/fixed_flat_set.h"
#include "base/containers/map_util.h"
#include "base/files/file_path.h"
#include "components/content_settings/core/common/content_settings_types.h"

namespace catsxp_shields {

// Content/Web settings:
inline constexpr char kAds[] = "shieldsAds";
inline constexpr char kCosmeticFiltering[] = "cosmeticFilteringV2";
inline constexpr char kTrackers[] = "trackers";
inline constexpr char kHTTPUpgradableResources[] = "httpUpgradableResources";
inline constexpr char kHTTPSUpgrades[] = "httpsUpgrades";
inline constexpr char kJavaScript[] = "javascript";
inline constexpr char kFingerprintingV2[] = "fingerprintingV2";
inline constexpr char kCatsxpShields[] = "catsxpShields";
inline constexpr char kCatsxpShieldsMetadata[] = "catsxpShieldsMetadata";
inline constexpr char kReferrers[] = "referrers";
inline constexpr char kCookies[] = "shieldsCookiesV3";
inline constexpr char kCatsxpAutoShred[] = "catsxpAutoShred";

// Prefs:
inline constexpr char kFacebookEmbeds[] = "fb-embeds";
inline constexpr char kTwitterEmbeds[] = "twitter-embeds";
inline constexpr char kLinkedInEmbeds[] = "linked-in-embeds";

inline constexpr auto kShieldsContentSettingsTypes =
    base::MakeFixedFlatSet<ContentSettingsType>({
        ContentSettingsType::CATSXP_ADS,
        ContentSettingsType::CATSXP_COSMETIC_FILTERING,
        ContentSettingsType::CATSXP_TRACKERS,
        ContentSettingsType::CATSXP_HTTP_UPGRADABLE_RESOURCES,
        ContentSettingsType::CATSXP_FINGERPRINTING_V2,
        ContentSettingsType::CATSXP_SHIELDS,
        ContentSettingsType::CATSXP_REFERRERS,
        ContentSettingsType::CATSXP_COOKIES,
        ContentSettingsType::CATSXP_AUTO_SHRED,
    });

using ShieldsContentSettingsTypes = decltype(kShieldsContentSettingsTypes);

inline constexpr auto kShieldsContentTypeNames =
    base::MakeFixedFlatMap<ContentSettingsType, const char*>({
        {ContentSettingsType::CATSXP_ADS, kAds},
        {ContentSettingsType::CATSXP_COSMETIC_FILTERING, kCosmeticFiltering},
        {ContentSettingsType::CATSXP_TRACKERS, kTrackers},
        {ContentSettingsType::CATSXP_HTTP_UPGRADABLE_RESOURCES,
         kHTTPUpgradableResources},
        {ContentSettingsType::CATSXP_HTTPS_UPGRADE, kHTTPSUpgrades},
        {ContentSettingsType::JAVASCRIPT, kJavaScript},
        {ContentSettingsType::CATSXP_FINGERPRINTING_V2, kFingerprintingV2},
        {ContentSettingsType::CATSXP_SHIELDS, kCatsxpShields},
        {ContentSettingsType::CATSXP_SHIELDS_METADATA, kCatsxpShieldsMetadata},
        {ContentSettingsType::CATSXP_REFERRERS, kReferrers},
        {ContentSettingsType::CATSXP_COOKIES, kCookies},
        {ContentSettingsType::CATSXP_AUTO_SHRED, kCatsxpAutoShred},
    });

using ShieldsContentTypeNames = decltype(kShieldsContentTypeNames);

namespace internal {
consteval bool CheckShieldsContentTypeNames() {
  for (const auto& [key_a, value_a] : kShieldsContentTypeNames) {
    for (const auto& [key_b, value_b] : kShieldsContentTypeNames) {
      if (key_a == key_b) {
        continue;
      }
      if (!value_a || !value_b || value_a == value_b) {
        // Name is null or not unique.
        return false;
      }
    }
  }
  return true;
}

static_assert(
    CheckShieldsContentTypeNames(),
    "Invalid kShieldsContentTypeNames. Name should be unique and non-null.");
}  // namespace internal

// Values used before the migration away from ResourceIdentifier, kept
// around for migration purposes only.
inline constexpr char kObsoleteAds[] = "ads";
inline constexpr char kObsoleteCookies[] = "cookies";
inline constexpr char kObsoleteShieldsCookies[] = "shieldsCookies";
inline constexpr char kObsoleteCosmeticFiltering[] = "cosmeticFiltering";

// Key for procedural and action filters in the UrlCosmeticResources struct from
// adblock-rust
inline constexpr char kCosmeticResourcesProceduralActions[] =
    "procedural_actions";

// Some users were not properly migrated from fingerprinting V1.
inline constexpr char kObsoleteFingerprinting[] = "fingerprinting";

// Filename for cached text from a custom filter list subscription
const base::FilePath::CharType kCustomSubscriptionListText[] =
    FILE_PATH_LITERAL("list_text.txt");

inline constexpr char kDefaultAdblockFiltersListUuid[] = "default";
inline constexpr char kFirstPartyAdblockFiltersListUuid[] =
    "E99CBD02-FFD1-4651-9BDD-6A9ED7B87819";
inline constexpr char kCookieListUuid[] =
    "AC023D22-AE88-4060-A978-4FEEEC4221693";
inline constexpr char kMobileNotificationsListUuid[] =
    "2F3DCE16-A19A-493C-A88F-2E110FBD37D6";
inline constexpr char kExperimentalListUuid[] =
    "564C3B75-8731-404C-AD7C-5683258BA0B0";
inline constexpr char kAdblockOnlySupplementalListUuid[] =
    "61C6046C-B040-4CE4-8C8E-F3E8F316AA72";

inline constexpr char kAdBlockResourceComponentName[] = "Catsxp Ad Block Resources Library";
inline constexpr char kAdBlockResourceComponentId[] = "ogolnieebfnhlpjoapigplimhmkhglod";
inline constexpr char kAdBlockResourceComponentBase64PublicKey[] =
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtSiUv4qoPWowsyXh+HSA"
    "oFiYGxL5sozbTAtNN54TkKQL4aGNS2HYKd7Ad++ePYab6rb08nYwaIQB9IH8DevU"
    "lv2VtT50TL3V0GF+es7McRXnMeRCy9dFyflJY6B/CV+Oo6HPUkvs9w0sVAC9AWY8"
    "lrJLE4D4AAW/j5Kw4KDT3U80XlDSrAeki0WfK5q2AFoqbziHs2HIFwzs8BhmxbeR"
    "gp3TAlNLdCXUo53F2Mh9NC3U08kdJd0HwmPYEb03BA8cmRFnLJ4f1AMCmJTm5mg7"
    "s7NtOZKn+dpWa3zD9EEE40zERLCd0MxtuOsOa8g38pVFSjF2n3JWySSZr9BWlm/"
    "WcwIDAQAB";

inline constexpr char kAdBlockFilterListCatalogComponentName[] =
    "Catsxp Ad Block List Catalog";
inline constexpr char kAdBlockFilterListCatalogComponentId[] =
    "kfccjfggmjndcomiakdamhplllepilok";
inline constexpr char kAdBlockFilterListCatalogComponentBase64PublicKey[] =
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAu/Gn2aBg7ckSOLkQpGYM"
    "cHksFzmCYMFsPwVI12EvvAW1Ez0DStCO9anueNGq59zLc2/FMxt2/kv0zEwIPtR2"
    "rGyp85Mc5O7IfLaaklIJZ+IHyCDebHj//MSrH3moPFuOL9+L7MrD6y5C0BwqkWJO"
    "ckw78bj5JgvrhW2rKJtqRImxKx8Vp+4/g6XJsI2zKZv+tbqxipJz4nJ67v2XSyai"
    "kmNUvSzBOlJ6HcX3k2CHWW7q5XKP4wyJbsZsdumzefrIoHorbkfCB5vsGo+OxEgt"
    "9aZazvNAc1ZNNO17RNpxbGBD5t8Jk8kk1Fm2h/zOdLcIR6t9BpL6UJzx3r3JvaVW"
    "/wIDAQAB";

inline constexpr char kCookieListEnabledHistogram[] =
    "Catsxp.Shields.CookieListEnabled";
inline constexpr char kCookieListPromptHistogram[] =
    "Catsxp.Shields.CookieListPrompt";

// The list of UUIDs of filter lists that will be loaded by AdBlockOnlyMode.
inline constexpr auto kAdblockOnlyModeFilterListUUIDs =
    base::MakeFixedFlatSet<std::string_view>(
        {kDefaultAdblockFiltersListUuid, kFirstPartyAdblockFiltersListUuid,
         kAdblockOnlySupplementalListUuid});

// The list of language codes that are supported by Ad Block Only mode.
inline constexpr auto kAdblockOnlyModeSupportedLanguageCodes =
    base::MakeFixedFlatSet<std::string_view>({"en"});

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_CATSXP_SHIELD_CONSTANTS_H_
