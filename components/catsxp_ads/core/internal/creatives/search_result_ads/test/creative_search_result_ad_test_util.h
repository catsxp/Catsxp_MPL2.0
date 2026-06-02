/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_TEST_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_TEST_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::test {

mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAd(
    bool use_random_uuids);
mojom::CreativeSearchResultAdInfoPtr BuildCreativeSearchResultAdWithConversion(
    bool use_random_uuids);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_SEARCH_RESULT_ADS_TEST_CREATIVE_SEARCH_RESULT_AD_TEST_UTIL_H_
