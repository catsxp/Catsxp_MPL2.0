/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_builder.h"

#include "base/check.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

DepositInfo FromMojomBuildDeposit(
    const mojom::CreativeSearchResultAdInfoPtr& mojom_creative_ad) {
  CHECK(mojom_creative_ad);

  return DepositInfo{
      .creative_instance_id = mojom_creative_ad->creative_instance_id,
      .value = mojom_creative_ad->value,
      .expire_at = base::Time::Now() + base::Hours(1),
  };
}

}  // namespace catsxp_ads
