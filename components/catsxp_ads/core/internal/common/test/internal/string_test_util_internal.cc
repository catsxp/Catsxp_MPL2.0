/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/string_test_util_internal.h"

#include <vector>

#include "base/strings/strcat.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"

namespace catsxp_ads::test {

std::string CapitalizeFirstCharacterOfEachWordAndTrimWhitespace(
    const std::string& value) {
  std::vector<std::string> components = base::SplitString(
      value, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

  for (auto& component : components) {
    component[0] = base::ToUpperASCII(component[0]);
  }

  return base::StrCat(components);
}

}  // namespace catsxp_ads::test
