/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_PREF_NAMES_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_PREF_NAMES_H_

namespace catsxp_shields {
namespace prefs {

inline constexpr char kAdBlockCheckedDefaultRegion[] =
    "catsxp.ad_block.checked_default_region";
inline constexpr char kAdBlockCheckedAllDefaultRegions[] =
    "catsxp.ad_block.checked_all_default_regions";
inline constexpr char kAdBlockCookieListOptInShown[] =
    "catsxp.ad_block.cookie_list_opt_in_shown";
inline constexpr char kAdBlockCookieListSettingTouched[] =
    "catsxp.ad_block.cookie_list_setting_touched";
inline constexpr char kAdBlockMobileNotificationsListSettingTouched[] =
    "catsxp.ad_block.mobile_notifications_list_setting_touched";

inline constexpr char kAdBlockCustomFilters[] = "catsxp.ad_block.custom_filters";
inline constexpr char kAdBlockRegionalFilters[] =
    "catsxp.ad_block.regional_filters";
inline constexpr char kAdBlockListSubscriptions[] =
    "catsxp.ad_block.list_subscriptions";
inline constexpr char kAdBlockDeveloperMode[] = "catsxp.ad_block.developer_mode";

inline constexpr char kMigratedAdblockSocialMediaBlockingSettings[] =
    "catsxp.migrated_adblock_social_media_blocking_settings";
inline constexpr char kFBEmbedControlType[] = "catsxp.shields.fb_embed_default";
inline constexpr char kTwitterEmbedControlType[] =
    "catsxp.shields.twitter_embed_default";
inline constexpr char kLinkedInEmbedControlType[] =
    "catsxp.shields.linkedin_embed_default";

inline constexpr char kReduceLanguageEnabled[] = "catsxp.reduce_language";

inline constexpr char kAdBlockOnlyModeEnabled[] =
    "catsxp.shields.adblock_only_mode_enabled";
inline constexpr char kAdBlockOnlyModeWasEnabledForSupportedLocale[] =
    "catsxp.shields.adblock_only_mode_was_enabled_for_supported_locale";
inline constexpr char kShieldsDisabledCount[] = "catsxp.shields.disabled_count";
inline constexpr char kAdBlockOnlyModePromptDismissed[] =
    "catsxp.shields.adblock_only_mode_prompt_dismissed";
inline constexpr char kAllowElementBlockerInPrivateMode[] =
    "catsxp.allow_element_blocker_in_private_mode";
inline constexpr char kShredBrowsingHistoryEnabled[] =
    "catsxp.shields.shred_browsing_history";

}  // namespace prefs
}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_PREF_NAMES_H_
