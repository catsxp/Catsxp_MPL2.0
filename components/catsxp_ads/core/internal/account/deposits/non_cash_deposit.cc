/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/non_cash_deposit.h"

#include <utility>

namespace catsxp_ads {

void NonCashDeposit::GetValue(const std::string& /*creative_instance_id*/,
                              GetDepositCallback callback) {
  std::move(callback).Run(/*success=*/true, /* value=*/0.0);
}

}  // namespace catsxp_ads
