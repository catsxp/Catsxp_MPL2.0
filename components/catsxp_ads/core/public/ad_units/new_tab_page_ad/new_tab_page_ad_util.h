/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_UTIL_H_

#include <optional>

#include "base/types/optional_ref.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct NewTabPageAdInfo;

mojom::NewTabPageAdInfoPtr ToMojom(
    base::optional_ref<const NewTabPageAdInfo> ad);
std::optional<NewTabPageAdInfo> FromMojom(const mojom::NewTabPageAdInfoPtr& ad);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_NEW_TAB_PAGE_AD_NEW_TAB_PAGE_AD_UTIL_H_
