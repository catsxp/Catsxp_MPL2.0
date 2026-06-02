/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/service/test/ads_service_mock.h"

namespace catsxp_ads {

AdsServiceMock::AdsServiceMock() : AdsService(/*delegate=*/nullptr) {}

AdsServiceMock::~AdsServiceMock() = default;

}  // namespace catsxp_ads
