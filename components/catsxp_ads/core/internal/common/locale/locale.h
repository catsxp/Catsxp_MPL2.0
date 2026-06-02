/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LOCALE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LOCALE_H_

#include <string>

namespace catsxp_ads {

// Provides the device locale (language and country codes). Tests may inject a
// controlled value via SetForTesting to decouple locale-sensitive logic from
// the real device locale.
class Locale {
 public:
  static const Locale& GetInstance();

  static void SetForTesting(const Locale* locale);

  Locale();

  Locale(const Locale&) = delete;
  Locale& operator=(const Locale&) = delete;

  virtual ~Locale();

  virtual std::string GetLanguageCode() const;
  virtual std::string GetCountryCode() const;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_LOCALE_LOCALE_H_
