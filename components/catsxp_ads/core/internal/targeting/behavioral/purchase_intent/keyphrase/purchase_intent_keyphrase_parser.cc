/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_parser.h"

#include <iomanip>
#include <sstream>

#include "base/strings/string_util.h"

namespace catsxp_ads {

KeywordList ParseKeyphrase(const std::string& keyphrase) {
  std::istringstream iss(base::ToLowerASCII(keyphrase));

  KeywordList keywords;

  std::string keyword;
  while (iss >> std::quoted(keyword)) {
    keywords.emplace_back(
        base::TrimString(keyword, " ", base::TrimPositions::TRIM_ALL));
  }

  return keywords;
}

}  // namespace catsxp_ads
