/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::test {

std::optional<mojom::UrlResponseInfo> GetNextUrlResponseForRequest(
    const mojom::UrlRequestInfoPtr& mojom_url_request,
    const URLResponseMap& url_responses);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_URL_RESPONSE_TEST_UTIL_INTERNAL_H_
