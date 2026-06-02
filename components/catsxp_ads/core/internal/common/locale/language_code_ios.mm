/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/locale/language_code.h"

#import <Foundation/Foundation.h>

#include <optional>

#include "base/strings/sys_string_conversions.h"

namespace catsxp_ads {

std::optional<std::string> MaybeGetLanguageCodeString() {
  return base::SysNSStringToUTF8(NSLocale.currentLocale.languageCode);
}

}  // namespace catsxp_ads
