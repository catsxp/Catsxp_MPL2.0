/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_SITE_HISTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_SITE_HISTORY_H_

#include <vector>

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "url/gurl.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

using SiteHistoryList = std::vector<GURL>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_SITE_HISTORY_H_
