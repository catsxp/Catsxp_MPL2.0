/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_ROTATING_HASH_USER_DATA_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_ROTATING_HASH_USER_DATA_UTIL_H_

#include <optional>
#include <string>

namespace catsxp_ads {

struct TransactionInfo;

std::optional<std::string> BuildRotatingHash(
    const TransactionInfo& transaction);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_ROTATING_HASH_USER_DATA_UTIL_H_
