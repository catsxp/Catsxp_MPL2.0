/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_version.h"

#include "base/check_is_test.h"
#include "base/no_destructor.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_util.h"
#include "catsxp/components/version_info/version_info.h"

namespace catsxp_ads {

namespace {

const BrowserVersion* g_browser_version_for_testing = nullptr;

}  // namespace

// static
const BrowserVersion& BrowserVersion::GetInstance() {
  if (g_browser_version_for_testing) {
    CHECK_IS_TEST();

    return *g_browser_version_for_testing;
  }

  static const base::NoDestructor<BrowserVersion> kBrowserVersion;
  return *kBrowserVersion;
}

// static
void BrowserVersion::SetForTesting(  // IN-TEST
    const BrowserVersion* const browser_version) {
  CHECK_IS_TEST();

  g_browser_version_for_testing = browser_version;
  ResetBrowserUpgradeCacheForTesting();  // IN-TEST
}

BrowserVersion::BrowserVersion() = default;

BrowserVersion::~BrowserVersion() = default;

std::string BrowserVersion::GetNumber() const {
  return version_info::GetCatsxpChromiumVersionNumber();
}

}  // namespace catsxp_ads
