/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/application_state/test/fake_browser_version.h"

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_util.h"

namespace catsxp_ads::test {

FakeBrowserVersion::FakeBrowserVersion() {
  BrowserVersion::SetForTesting(this);
}

FakeBrowserVersion::~FakeBrowserVersion() {
  BrowserVersion::SetForTesting(nullptr);
}

void FakeBrowserVersion::SetNumber(std::string number) {
  number_ = std::move(number);
  ResetBrowserUpgradeCacheForTesting();
}

std::string FakeBrowserVersion::GetNumber() const {
  return number_;
}

}  // namespace catsxp_ads::test
