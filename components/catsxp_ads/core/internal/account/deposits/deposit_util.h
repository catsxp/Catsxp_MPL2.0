/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_UTIL_H_

#include <string>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

void DepositWithUserData(mojom::AdType ad_type,
                         mojom::ConfirmationType confirmation_type,
                         const std::string& campaign_id,
                         const std::string& creative_instance_id,
                         const std::string& segment,
                         base::DictValue user_data);

void Deposit(mojom::AdType ad_type,
             mojom::ConfirmationType confirmation_type,
             const std::string& campaign_id,
             const std::string& creative_instance_id,
             const std::string& segment);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_UTIL_H_
