/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_FAKE_BROWSER_VERSION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_FAKE_BROWSER_VERSION_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_version.h"

namespace catsxp_ads::test {

inline constexpr char kDefaultBrowserVersionNumber[] = "1.2.3.4";

// A test double for `BrowserVersion` that installs itself as the active
// instance on construction and restores the default on destruction. Call
// `SetNumber` to change the simulated version at any point during a test.
class FakeBrowserVersion final : public BrowserVersion {
 public:
  FakeBrowserVersion();

  FakeBrowserVersion(const FakeBrowserVersion&) = delete;
  FakeBrowserVersion& operator=(const FakeBrowserVersion&) = delete;

  ~FakeBrowserVersion() override;

  void SetNumber(std::string number);

  // BrowserVersion:
  std::string GetNumber() const override;

 private:
  std::string number_ = kDefaultBrowserVersionNumber;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_TEST_FAKE_BROWSER_VERSION_H_
