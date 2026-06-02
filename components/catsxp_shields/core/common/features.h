/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_FEATURES_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_FEATURES_H_

#include <cstddef>
#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"

namespace catsxp_shields {
namespace features {
BASE_DECLARE_FEATURE(kAdBlockDefaultResourceUpdateInterval);
BASE_DECLARE_FEATURE(kCatsxpAdblockCnameUncloaking);
BASE_DECLARE_FEATURE(kCatsxpAdblockCollapseBlockedElements);
BASE_DECLARE_FEATURE(kCatsxpAdblockCookieListDefault);
BASE_DECLARE_FEATURE(kCatsxpAdblockCosmeticFiltering);
BASE_DECLARE_FEATURE(kCatsxpAdblockProceduralFiltering);
BASE_DECLARE_FEATURE(kCatsxpAdblockCspRules);
BASE_DECLARE_FEATURE(kCatsxpAdblockDefault1pBlocking);
BASE_DECLARE_FEATURE(kCatsxpAdblockMobileNotificationsListDefault);
BASE_DECLARE_FEATURE(kCatsxpAdblockExperimentalListDefault);
BASE_DECLARE_FEATURE(kCatsxpAdblockScriptletDebugLogs);
BASE_DECLARE_FEATURE(kCatsxpAdblockShowHiddenComponents);
BASE_DECLARE_FEATURE(kCatsxpDarkModeBlock);
BASE_DECLARE_FEATURE(kCatsxpDomainBlock);
BASE_DECLARE_FEATURE(kCatsxpDomainBlock1PES);
BASE_DECLARE_FEATURE(kCatsxpExtensionNetworkBlocking);
BASE_DECLARE_FEATURE(kCatsxpFarbling);
BASE_DECLARE_FEATURE(kCatsxpReduceLanguage);
BASE_DECLARE_FEATURE(kCatsxpShredFeature);
BASE_DECLARE_FEATURE(kCatsxpShredCacheData);
BASE_DECLARE_FEATURE(kCatsxpShieldsContentSettingsIOS);
BASE_DECLARE_FEATURE(kCatsxpIOSDebugAdblock);
BASE_DECLARE_FEATURE(kCatsxpIOSEnableFarblingPlugins);
BASE_DECLARE_FEATURE(kCatsxpShowStrictFingerprintingMode);
BASE_DECLARE_FEATURE(kCosmeticFilteringExtraPerfMetrics);
BASE_DECLARE_FEATURE(kCosmeticFilteringJsPerformance);
BASE_DECLARE_FEATURE(kCosmeticFilteringSyncLoad);
BASE_DECLARE_FEATURE(kBlockAllCookiesToggle);
BASE_DECLARE_FEATURE(kCatsxpShieldsElementPicker);
BASE_DECLARE_FEATURE(kWebKitAdvancedPrivacyProtections);
extern const base::FeatureParam<int> kComponentUpdateCheckIntervalMins;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringSubFrameFirstSelectorsPollingDelayMs;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringswitchToSelectorsPollingThreshold;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringFetchNewClassIdRulesThrottlingMs;
BASE_DECLARE_FEATURE(kAdblockOverrideRegexDiscardPolicy);
extern const base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyCleanupIntervalSec;
extern const base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyDiscardUnusedSec;

BASE_DECLARE_FEATURE(kAdblockOnlyMode);
// The number of times the shields are disabled before showing the Ad Block Only
// mode prompt in Shields Panel.
inline constexpr base::FeatureParam<int>
    kAdblockOnlyModePromptAfterShieldsDisabledCount{
        &kAdblockOnlyMode, "prompt_after_shields_disabled_count", 5};
// The time interval after which the Ad Block Only mode repeated reloads prompt
// is shown.
inline constexpr base::FeatureParam<base::TimeDelta>
    kAdblockOnlyModePromptAfterPageReloadsInterval{
        &kAdblockOnlyMode, "prompt_after_page_reloads_interval",
        base::Seconds(10)};
// The minimum number of times the page is reloaded before showing the Ad Block
// Only mode repeated reloads prompt.
inline constexpr base::FeatureParam<size_t>
    kAdblockOnlyModePromptAfterPageReloadsMin{
        &kAdblockOnlyMode, "prompt_after_page_reloads_min", 0};
// The maximum number of times the page is reloaded before showing the Ad Block
// Only mode repeated reloads prompt.
inline constexpr base::FeatureParam<size_t>
    kAdblockOnlyModePromptAfterPageReloadsMax{
        &kAdblockOnlyMode, "prompt_after_page_reloads_max", 0};

BASE_DECLARE_FEATURE(kShowUpdatedShieldsPanel);

BASE_DECLARE_FEATURE(kAdblockDATCache);

}  // namespace features
}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_COMMON_FEATURES_H_
