/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/locale/locale.h"

namespace catsxp_ads {

std::string CurrentLanguageCode() {
  return Locale::GetInstance().GetLanguageCode();
}

std::string CurrentCountryCode() {
  return Locale::GetInstance().GetCountryCode();
}

}  // namespace catsxp_ads
