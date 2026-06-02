/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_UTIL_H_

#include <cstdint>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {

bool IsAllowedToLandOnPage(mojom::AdType mojom_ad_type);

bool ShouldResumePageLand(int32_t tab_id);

bool DidLandOnPage(int32_t tab_id, const GURL& url);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_UTIL_H_
