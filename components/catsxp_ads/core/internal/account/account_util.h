/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

bool IsAllowedToDeposit(const std::string& creative_instance_id,
                        mojom::AdType mojom_ad_type,
                        mojom::ConfirmationType mojom_confirmation_type);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_UTIL_H_
