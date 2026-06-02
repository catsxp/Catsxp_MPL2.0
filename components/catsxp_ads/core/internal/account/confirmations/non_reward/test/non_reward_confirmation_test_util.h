/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_NON_REWARD_TEST_NON_REWARD_CONFIRMATION_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_NON_REWARD_TEST_NON_REWARD_CONFIRMATION_TEST_UTIL_H_

#include <optional>

namespace catsxp_ads {

struct ConfirmationInfo;

namespace test {

std::optional<ConfirmationInfo> BuildNonRewardConfirmation(
    bool use_random_uuids);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_NON_REWARD_TEST_NON_REWARD_CONFIRMATION_TEST_UTIL_H_
