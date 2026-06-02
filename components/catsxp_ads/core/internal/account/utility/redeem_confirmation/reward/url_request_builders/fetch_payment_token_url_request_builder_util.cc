/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildFetchPaymentTokenUrlPath(const std::string& transaction_id) {
  return absl::StrFormat("/v%d/confirmation/%s/paymentToken",
                         kTokensServerVersion, transaction_id);
}

}  // namespace catsxp_ads
