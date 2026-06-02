/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_USER_DATA_BUILDER_CONFIRMATION_USER_DATA_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_USER_DATA_BUILDER_CONFIRMATION_USER_DATA_BUILDER_H_

#include "base/values.h"

namespace catsxp_ads {

struct TransactionInfo;
struct UserDataInfo;

UserDataInfo BuildConfirmationUserData(const TransactionInfo& transaction,
                                       base::DictValue user_data);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_USER_DATA_BUILDER_CONFIRMATION_USER_DATA_BUILDER_H_
