/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/get_signed_tokens_url_request_builder_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildGetSignedTokensUrlPath(const std::string& payment_id,
                                        const std::string& nonce) {
  CHECK(!payment_id.empty());
  CHECK(!nonce.empty());

  return absl::StrFormat("/v%d/confirmation/token/%s?nonce=%s",
                         kTokensServerVersion, payment_id, nonce);
}

}  // namespace catsxp_ads
