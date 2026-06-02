/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

namespace catsxp_ads {

bool NewTabPageAdInfo::IsValid() const {
  return AdInfo::IsValid() && !company_name.empty() && !alt.empty();
}

}  // namespace catsxp_ads
