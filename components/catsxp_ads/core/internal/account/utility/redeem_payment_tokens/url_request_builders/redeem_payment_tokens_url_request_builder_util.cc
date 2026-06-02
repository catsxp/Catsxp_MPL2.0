/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/url_request_builders/redeem_payment_tokens_url_request_builder_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildRedeemPaymentTokensUrlPath(const std::string& payment_id) {
  CHECK(!payment_id.empty());

  return absl::StrFormat("/v%d/confirmation/payment/%s", kTokensServerVersion,
                         payment_id);
}

}  // namespace catsxp_ads
