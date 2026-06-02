/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/country_code_user_data.h"

#include <string>
#include <string_view>

#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"
#include "components/variations/pref_names.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kCountryCodeKey = "countryCode";
}  // namespace

base::DictValue BuildCountryCodeUserData() {
  std::string country_code =
      GetLocalStateStringPref(variations::prefs::kVariationsCountry);
  if (country_code.empty()) {
    // If the variations country code is not set, use the device's current
    // country code as a fallback.
    country_code = CurrentCountryCode();
  }
  return base::DictValue().Set(kCountryCodeKey,
                               base::ToUpperASCII(country_code));
}

}  // namespace catsxp_ads
