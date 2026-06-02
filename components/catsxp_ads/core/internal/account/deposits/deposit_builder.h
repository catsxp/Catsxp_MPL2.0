/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_BUILDER_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct DepositInfo;

DepositInfo FromMojomBuildDeposit(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_BUILDER_H_
