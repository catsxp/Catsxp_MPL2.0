/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_TEST_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_TEST_AD_TEST_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct AdInfo;

namespace test {

std::string RandomUuidOr(bool should_generate_random_uuid,
                         const std::string& or_uuid);

AdInfo BuildAd(mojom::AdType mojom_ad_type, bool use_random_uuids);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_AD_UNITS_TEST_AD_TEST_UTIL_H_
