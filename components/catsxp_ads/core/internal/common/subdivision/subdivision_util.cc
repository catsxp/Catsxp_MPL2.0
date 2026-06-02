/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_util.h"

#include <vector>

#include "base/strings/string_split.h"

namespace catsxp_ads {

namespace {

std::vector<std::string> SplitComponents(const std::string& subdivision) {
  return base::SplitString(subdivision, "-", base::TRIM_WHITESPACE,
                           base::SPLIT_WANT_NONEMPTY);
}

}  // namespace

std::optional<std::string> GetSubdivisionCountryCode(
    const std::string& subdivision) {
  const std::vector<std::string> components = SplitComponents(subdivision);
  if (components.size() != 2) {
    return std::nullopt;
  }

  return components.front();
}

std::optional<std::string> GetSubdivisionCode(const std::string& subdivision) {
  const std::vector<std::string> components = SplitComponents(subdivision);
  if (components.size() != 2) {
    return std::nullopt;
  }

  return components.back();
}

}  // namespace catsxp_ads
