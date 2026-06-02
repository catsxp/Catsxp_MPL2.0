/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/studies/studies.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/studies/studies_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

Studies::Studies() {
  ads_client_observation_.Observe(&GetAdsClient());
}

Studies::~Studies() = default;

///////////////////////////////////////////////////////////////////////////////

void Studies::OnNotifyDidInitializeAds() {
  LogActiveFieldTrialStudyGroups();
}

}  // namespace catsxp_ads
