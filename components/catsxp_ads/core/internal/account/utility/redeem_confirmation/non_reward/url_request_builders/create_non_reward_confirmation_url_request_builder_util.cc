/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/url_request_builders/create_non_reward_confirmation_url_request_builder_util.h"

#include "base/check.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

namespace {
constexpr int kConfirmationServerVersion = 4;
}  // namespace

std::string BuildCreateNonRewardConfirmationUrlPath(
    const std::string& transaction_id) {
  CHECK(!transaction_id.empty());

  return absl::StrFormat("/v%d/confirmation/%s", kConfirmationServerVersion,
                         transaction_id);
}

}  // namespace catsxp_ads
