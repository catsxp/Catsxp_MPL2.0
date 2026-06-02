/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_INFO_H_

#include <string>

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct NewTabPageAdInfo final : AdInfo {
  [[nodiscard]] bool IsValid() const;

  std::string company_name;
  std::string alt;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_INFO_H_
