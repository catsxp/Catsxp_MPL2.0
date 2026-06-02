/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

namespace {

AdsCore& GetAdsCore() {
  CHECK(GlobalState::HasInstance());

  return GlobalState::GetInstance()->GetAdsCore();
}

}  // namespace

TokenGeneratorInterface* GetTokenGenerator() {
  return GetAdsCore().GetTokenGenerator();
}

Account& GetAccount() {
  return GetAdsCore().GetAccount();
}

AdHandler& GetAdHandler() {
  return GetAdsCore().GetAdHandler();
}

Reactions& GetReactions() {
  return GetAdsCore().GetReactions();
}

void UpdateReportMetricState(
    const std::string& creative_instance_id,
    mojom::NewTabPageAdMetricType mojom_ad_metric_type) {
  GetAdsCore().UpdateReportMetricState(creative_instance_id,
                                       mojom_ad_metric_type);
}

bool ShouldReportMetric(const std::string& creative_instance_id) {
  return GetAdsCore().ShouldReportMetric(creative_instance_id);
}

}  // namespace catsxp_ads
