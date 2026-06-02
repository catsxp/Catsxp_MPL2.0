/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/language_code.h"

#include <windows.h>

#include <optional>
#include <vector>

#include "base/strings/utf_string_conversions.h"

namespace catsxp_ads {

std::optional<std::string> MaybeGetLanguageCodeString() {
  const int buffer_size =
      ::GetLocaleInfoEx(/*lpLocaleName=*/nullptr,
                        /*LCType=*/LOCALE_SISO639LANGNAME, /*lpLCData=*/nullptr,
                        /*cchData=*/0);
  if (buffer_size == 0) {
    return std::nullopt;
  }

  std::vector<wchar_t> buffer(buffer_size);
  if (::GetLocaleInfoEx(
          /*lpLocaleName=*/nullptr, /*LCType=*/LOCALE_SISO639LANGNAME,
          /*lpLCData=*/buffer.data(), /*cchData=*/buffer_size) == 0) {
    return std::nullopt;
  }

  return base::WideToUTF8(buffer.data());
}

}  // namespace catsxp_ads
