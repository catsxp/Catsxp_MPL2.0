/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/account.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions.h"

namespace catsxp_ads {

class TokenGeneratorInterface;

// Provides methods for generating tokens for refilling and redeeming
// confirmation tokens.
TokenGeneratorInterface* GetTokenGenerator();

// Provides methods for managing user rewards, wallets, account statements, and
// deposits.
Account& GetAccount();

// Provides methods for serving and triggering events for various types of ads,
// including new tab page ads, notification ads, and search result ads.
AdHandler& GetAdHandler();

// Provides methods for engaging with ads, such as liking, disliking, marking as
// inappropriate, and saving ads.
Reactions& GetReactions();

// Updates the reporting state for a creative instance ID, enabling or
// disabling metrics reporting.
void UpdateReportMetricState(
    const std::string& creative_instance_id,
    mojom::NewTabPageAdMetricType mojom_ad_metric_type);

// Returns true if metrics should be reported for the given creative instance
// ID, otherwise false.
bool ShouldReportMetric(const std::string& creative_instance_id);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_UTIL_H_
