/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"

namespace catsxp_ads {

bool SearchResultAdInfo::IsValid() const {
  return AdInfo::IsValid() && !headline_text.empty() && !description.empty();
}

}  // namespace catsxp_ads
