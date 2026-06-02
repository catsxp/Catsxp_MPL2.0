/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_VERSION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_VERSION_H_

#include <string>

namespace catsxp_ads {

// Provides the current browser version number. Tests may inject a controlled
// value via SetForTesting to decouple version-sensitive logic from the real
// browser binary version.
class BrowserVersion {
 public:
  static const BrowserVersion& GetInstance();

  static void SetForTesting(const BrowserVersion* browser_version);

  BrowserVersion();

  BrowserVersion(const BrowserVersion&) = delete;
  BrowserVersion& operator=(const BrowserVersion&) = delete;

  virtual ~BrowserVersion();

  virtual std::string GetNumber() const;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_APPLICATION_STATE_BROWSER_VERSION_H_
