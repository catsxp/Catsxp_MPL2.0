/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/language_code.h"

#include <optional>
#include <string>
#include <string_view>

#include "base/android/locale_utils.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kDelimiters = "-_";
}  // namespace

std::optional<std::string> MaybeGetLanguageCodeString() {
  std::string locale = base::android::GetDefaultLocaleString();
  if (locale.empty()) {
    // Locale is not set.
    return std::nullopt;
  }

  const size_t pos = locale.find_first_of(kDelimiters);
  std::string language_code = locale.substr(0, pos);
  if (language_code.empty()) {
    return std::nullopt;
  }
  return language_code;
}

}  // namespace catsxp_ads
