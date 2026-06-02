/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace catsxp_ads {

struct ConfirmationInfo;
struct TransactionInfo;

std::optional<std::string> BuildRewardCredential(
    const ConfirmationInfo& confirmation);

std::optional<ConfirmationInfo> BuildRewardConfirmation(
    const TransactionInfo& transaction,
    base::DictValue user_data);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_UTIL_H_
