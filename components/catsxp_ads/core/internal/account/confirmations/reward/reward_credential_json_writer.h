/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CREDENTIAL_JSON_WRITER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CREDENTIAL_JSON_WRITER_H_

#include <optional>
#include <string>

#include "base/types/optional_ref.h"

namespace catsxp_ads {

struct RewardInfo;

namespace json::writer {

std::optional<std::string> WriteRewardCredential(
    base::optional_ref<const RewardInfo> reward,
    const std::string& payload);

}  // namespace json::writer

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CREDENTIAL_JSON_WRITER_H_
