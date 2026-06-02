/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/dynamic/confirmation_dynamic_user_data_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/fixed/confirmation_fixed_user_data_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/user_data_info.h"

namespace catsxp_ads {

UserDataInfo BuildConfirmationUserData(const TransactionInfo& transaction,
                                       base::DictValue user_data) {
  UserDataInfo confirmation_user_data;

  confirmation_user_data.dynamic = BuildDynamicUserData();

  confirmation_user_data.fixed = BuildFixedUserData(transaction);
  confirmation_user_data.fixed.Merge(std::move(user_data));

  return confirmation_user_data;
}

}  // namespace catsxp_ads
