/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/locale.h"

#include "base/check_is_test.h"
#include "base/no_destructor.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/locale/language_code.h"
#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"
#include "components/country_codes/country_codes.h"

namespace catsxp_ads {

namespace {

const Locale* g_locale_for_testing = nullptr;

std::string BuildCountryCode() {
  const country_codes::CountryId country_id =
      country_codes::GetCurrentCountryID();
  return country_id.IsValid() ? base::ToUpperASCII(country_id.CountryCode())
                              : kDefaultCountryCode;
}

}  // namespace

Locale::Locale() = default;

Locale::~Locale() = default;

// static
void Locale::SetForTesting(const Locale* const locale) {  // IN-TEST
  CHECK_IS_TEST();

  g_locale_for_testing = locale;
}

std::string Locale::GetLanguageCode() const {
  // ISO 639-1 language code (e.g. "en", "fr", "de").
  static const base::NoDestructor<std::string> kLanguageCode(base::ToLowerASCII(
      MaybeGetLanguageCodeString().value_or(kDefaultLanguageCode)));
  return *kLanguageCode;
}

std::string Locale::GetCountryCode() const {
  // ISO 3166-1 alpha-2 country code (e.g. "US", "FR", "DE").
  static const base::NoDestructor<std::string> kCountryCode(BuildCountryCode());
  return *kCountryCode;
}

// static
const Locale& Locale::GetInstance() {
  if (g_locale_for_testing) {
    CHECK_IS_TEST();

    return *g_locale_for_testing;
  }

  static const base::NoDestructor<Locale> kLocale;
  return *kLocale;
}

}  // namespace catsxp_ads
