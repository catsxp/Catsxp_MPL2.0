/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/version_number_user_data.h"

#include <string_view>

#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/application_state/browser_util.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kVersionNumberKey = "versionNumber";
}  // namespace

base::DictValue BuildVersionNumberUserData() {
  std::vector<std::string> parts =
      base::SplitString(GetBrowserVersionNumber(), ".", base::KEEP_WHITESPACE,
                        base::SPLIT_WANT_ALL);
  parts.reserve(4);

  parts.resize(4, "0");
  parts[2] = "0";
  parts[3] = "0";

  return base::DictValue().Set(kVersionNumberKey, base::JoinString(parts, "."));
}

}  // namespace catsxp_ads
