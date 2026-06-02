/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_interface.h"

namespace catsxp_ads {

class NonCashDeposit final : public DepositInterface {
 public:
  // DepositInterface:
  void GetValue(const std::string& creative_instance_id,
                GetDepositCallback callback) override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_
