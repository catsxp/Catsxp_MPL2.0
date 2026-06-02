/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/network_connection_permission_rule.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

bool HasNetworkConnectionPermission() {
  if (!kShouldOnlyServeAdsWithValidInternetConnection.Get()) {
    return true;
  }

  if (GetAdsClient().IsNetworkConnectionAvailable()) {
    return true;
  }

  BLOG(2, "Network connection is unavailable");
  return false;
}

}  // namespace catsxp_ads
