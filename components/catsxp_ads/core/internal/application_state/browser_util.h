/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_UTIL_H_

#include <string>

namespace catsxp_ads {

std::string GetBrowserVersionNumber();

bool WasBrowserUpgraded();

// Clears the cached WasBrowserUpgraded result so the next call re-evaluates
// against the current BrowserVersion. Called by BrowserVersion::SetForTesting
// whenever a fake is installed or removed.
void ResetBrowserUpgradeCacheForTesting();  // IN-TEST

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_UTIL_H_
