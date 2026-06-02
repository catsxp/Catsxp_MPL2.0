/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/request_signed_tokens/request_signed_tokens_url_request_builder_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_constants.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"

namespace catsxp_ads {

std::string BuildRequestSignedTokensUrlPath(const std::string& payment_id) {
  CHECK(!payment_id.empty());

  return absl::StrFormat("/v%d/confirmation/token/%s", kTokensServerVersion,
                         payment_id);
}

}  // namespace catsxp_ads
