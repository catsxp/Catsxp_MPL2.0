/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/test/search_result_ad_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/search_result_ads/test/creative_search_result_ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

SearchResultAdInfo BuildSearchResultAd(bool use_random_uuids) {
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      BuildCreativeSearchResultAd(use_random_uuids);
  return FromMojomBuildSearchResultAd(mojom_creative_ad);
}

}  // namespace catsxp_ads::test
