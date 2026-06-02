/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/common/features.h"

#include "base/feature_list.h"

namespace catsxp_shields::features {

BASE_FEATURE(kAdBlockDefaultResourceUpdateInterval,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Catsxp will block first-party requests that appear in a filter
// list when Shields is in "standard" blocking mode. When disabled, Catsxp will
// allow first-party requests in "standard" blocking mode regardless of whether
// or not they appear in a filter list.
BASE_FEATURE(kCatsxpAdblockDefault1pBlocking,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Catsxp will issue DNS queries for requests that the adblock
// engine has not blocked, then check them again with the original hostname
// substituted for any canonical name found.
BASE_FEATURE(kCatsxpAdblockCnameUncloaking,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Catsxp will apply HTML element collapsing to all images and
// iframes that initiate a blocked network request.
BASE_FEATURE(kCatsxpAdblockCollapseBlockedElements,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Catsxp will enable "Easylist-Cookie List" by default unless
// overridden by a locally set preference.
BASE_FEATURE(kCatsxpAdblockCookieListDefault,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kCatsxpAdblockCosmeticFiltering,
             base::FEATURE_ENABLED_BY_DEFAULT);
// Catsxp will apply cosmetic filters with procedural operators like
// `:has-text(...)` and `:upward(...)`.
BASE_FEATURE(kCatsxpAdblockProceduralFiltering,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kCatsxpAdblockScriptletDebugLogs,
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kCatsxpAdblockCspRules,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kCatsxpAdblockShowHiddenComponents,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Catsxp will enable "Fanboy's Mobile Notifications List" by
// default unless overridden by a locally set preference.
BASE_FEATURE(kCatsxpAdblockMobileNotificationsListDefault,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Catsxp will enable "Catsxp Experimental Adblock Rules" list by
// default unless overridden by a locally set preference.
// NOTE: this should only be turned on by default in Nightly and Beta.
BASE_FEATURE(kCatsxpAdblockExperimentalListDefault,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Catsxp will block domains listed in the user's selected adblock
// filters and present a security interstitial with choice to proceed and
// optionally whitelist the domain.
// Domain block filters look like this:
// ||ads.example.com^
BASE_FEATURE(kCatsxpDomainBlock,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Catsxp will attempt to enable 1PES mode in a standard blocking
// mode when a user visists a domain that is present in currently active adblock
// filters. 1PES will be enabled only if neither cookies nor localStorage data
// is stored for the website.
BASE_FEATURE(kCatsxpDomainBlock1PES,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, network requests initiated by extensions will be checked and
// potentially blocked by Catsxp Shields.
BASE_FEATURE(kCatsxpExtensionNetworkBlocking,
             base::FEATURE_DISABLED_BY_DEFAULT);
// Enables Catsxp farbling (randomization of fingerprinting-susceptible WebAPIs).
BASE_FEATURE(kCatsxpFarbling, base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, language headers and APIs may be altered by Catsxp Shields.
BASE_FEATURE(kCatsxpReduceLanguage,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, catsxp shred feature will be available
BASE_FEATURE(kCatsxpShredFeature,
#if BUILDFLAG(IS_IOS) || BUILDFLAG(IS_ANDROID)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// When enabled, catsxp shred will clear all cache data when shredding.
BASE_FEATURE(kCatsxpShredCacheData,
#if BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// When enabled, catsxp will use content settings for Shields on iOS.
BASE_FEATURE(kCatsxpShieldsContentSettingsIOS, base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, will display debug menu for adblock features in the Shields
// panel.
BASE_FEATURE(kCatsxpIOSDebugAdblock,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, will farble navigator.plugins.
BASE_FEATURE(kCatsxpIOSEnableFarblingPlugins,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, show Strict (aggressive) fingerprinting mode in Catsxp Shields.
BASE_FEATURE(kCatsxpShowStrictFingerprintingMode,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Catsxp will always report Light in Fingerprinting: Strict mode
BASE_FEATURE(kCatsxpDarkModeBlock,
             base::FEATURE_ENABLED_BY_DEFAULT);
// load the cosmetic filter rules using sync ipc
BASE_FEATURE(kCosmeticFilteringSyncLoad,
             "CosmeticFilterSyncLoad",
             base::FEATURE_ENABLED_BY_DEFAULT);
// If the feature flag is on, we show the Block all Cookies toggle
BASE_FEATURE(kBlockAllCookiesToggle,
#if BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// when enabled, allow to select and block HTML elements
BASE_FEATURE(kCatsxpShieldsElementPicker,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kAdblockOnlyMode,
             base::FEATURE_DISABLED_BY_DEFAULT);

// Enables extra TRACE_EVENTs in content filter js. The feature is
// primary designed for local debugging.
BASE_FEATURE(kCosmeticFilteringExtraPerfMetrics,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kCosmeticFilteringJsPerformance,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kWebKitAdvancedPrivacyProtections,
             base::FEATURE_DISABLED_BY_DEFAULT);

constexpr base::FeatureParam<int> kComponentUpdateCheckIntervalMins{
    &kAdBlockDefaultResourceUpdateInterval, "update_interval_mins", 100};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringSubFrameFirstSelectorsPollingDelayMs{
        &kCosmeticFilteringJsPerformance, "subframes_first_query_delay_ms",
        "1000"};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringswitchToSelectorsPollingThreshold{
        &kCosmeticFilteringJsPerformance, "switch_to_polling_threshold",
        "1000"};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringFetchNewClassIdRulesThrottlingMs{
        &kCosmeticFilteringJsPerformance, "fetch_throttling_ms", "100"};

BASE_FEATURE(kAdblockOverrideRegexDiscardPolicy,
             base::FEATURE_DISABLED_BY_DEFAULT);

constexpr base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyCleanupIntervalSec{
        &kAdblockOverrideRegexDiscardPolicy, "cleanup_interval_sec", 0};

constexpr base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyDiscardUnusedSec{
        &kAdblockOverrideRegexDiscardPolicy, "discard_unused_sec", 180};

BASE_FEATURE(kShowUpdatedShieldsPanel, base::FEATURE_ENABLED_BY_DEFAULT);

// When enabled, adblock engines are serialized to DAT files on disk after
// filter set loading. On subsequent startups, the cached DAT is loaded
// instead of reprocessing filter lists, improving startup time.
BASE_FEATURE(kAdblockDATCache, base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace catsxp_shields::features
