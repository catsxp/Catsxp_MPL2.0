/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildCreateRewardConfirmationUrlPath(
    const std::string& transaction_id,
    const std::string& credential_base64url) {
  CHECK(!transaction_id.empty());
  CHECK(!credential_base64url.empty());

  return absl::StrFormat("/v%d/confirmation/%s/%s", kTokensServerVersion,
                         transaction_id, credential_base64url);
}

}  // namespace catsxp_ads
