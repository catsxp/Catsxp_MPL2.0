/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/request_signed_tokens/request_signed_tokens_url_request_util.h"

#include <string_view>

#include "base/values.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kIsEligibleKey = "isEligible";
constexpr std::string_view kNonceKey = "nonce";

}  // namespace

std::optional<bool> ParseIsEligible(const base::DictValue& dict) {
  return dict.FindBool(kIsEligibleKey);
}

std::optional<std::string> ParseNonce(const base::DictValue& dict) {
  const std::string* const nonce = dict.FindString(kNonceKey);
  if (!nonce || nonce->empty()) {
    return std::nullopt;
  }

  return *nonce;
}

}  // namespace catsxp_ads
