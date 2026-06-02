/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_info.h"

namespace catsxp_ads {

bool DepositInfo::IsValid() const {
  return !creative_instance_id.empty();
}

}  // namespace catsxp_ads
