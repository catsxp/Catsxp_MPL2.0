/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/language_code.h"

#include <locale.h>

#include <optional>
#include <string>
#include <string_view>

namespace catsxp_ads {

namespace {
constexpr std::string_view kDelimiters = "-_";
}  // namespace

std::optional<std::string> MaybeGetLanguageCodeString() {
  const char* locale = setlocale(LC_MESSAGES, nullptr);
  if (!locale) {
    // Locale is not set.
    return std::nullopt;
  }
  std::string locale_string(locale);

  const size_t pos = locale_string.find_first_of(kDelimiters);
  std::string language_code = locale_string.substr(0, pos);
  if (language_code.empty() || language_code == "C" ||
      language_code == "POSIX") {
    // Standard C locale.
    return std::nullopt;
  }
  return language_code;
}

}  // namespace catsxp_ads
