/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

struct SearchResultAdInfo final : AdInfo {
  [[nodiscard]] bool IsValid() const;

  std::string headline_text;
  std::string description;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_
