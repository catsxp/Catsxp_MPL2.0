/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_CASH_DEPOSIT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_CASH_DEPOSIT_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_interface.h"
#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposits_database_table.h"

namespace catsxp_ads {

class CashDeposit final : public DepositInterface {
 public:
  // DepositInterface:
  void GetValue(const std::string& creative_instance_id,
                GetDepositCallback callback) override;

 private:
  database::table::Deposits deposits_database_table_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_CASH_DEPOSIT_H_
