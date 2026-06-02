/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

AdsClient& GetAdsClient() {
  CHECK(GlobalState::HasInstance());

  return GlobalState::GetInstance()->GetAdsClient();
}

}  // namespace catsxp_ads
