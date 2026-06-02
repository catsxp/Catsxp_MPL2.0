/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DEPOSIT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DEPOSIT_INFO_H_

#include "base/time/time.h"

namespace catsxp_ads {

struct CreativeDepositInfo final {
  double value;
  base::Time expire_at;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CREATIVE_DEPOSIT_INFO_H_
