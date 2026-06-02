/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_TEST_FAKE_LOCALE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_TEST_FAKE_LOCALE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/locale/locale.h"
#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"

namespace catsxp_ads::test {

// A test double for `Locale` that installs itself as the active instance on
// construction and restores the default on destruction. Call `SetLanguageCode`
// or `SetCountryCode` to change the simulated locale at any point during a
// test.
class FakeLocale final : public Locale {
 public:
  FakeLocale();

  FakeLocale(const FakeLocale&) = delete;
  FakeLocale& operator=(const FakeLocale&) = delete;

  ~FakeLocale() override;

  void SetLanguageCode(const std::string& language_code);
  void SetCountryCode(const std::string& country_code);

  // Locale:
  std::string GetLanguageCode() const override;
  std::string GetCountryCode() const override;

 private:
  std::string language_code_ = kDefaultLanguageCode;
  std::string country_code_ = kDefaultCountryCode;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_TEST_FAKE_LOCALE_H_
