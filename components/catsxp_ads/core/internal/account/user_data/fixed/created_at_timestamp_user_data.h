/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_

#include "base/values.h"

namespace catsxp_ads {

struct TransactionInfo;

base::DictValue BuildCreatedAtTimestampUserData(
    const TransactionInfo& transaction);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_
