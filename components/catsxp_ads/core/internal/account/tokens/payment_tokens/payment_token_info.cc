/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace catsxp_ads {

PaymentTokenInfo::PaymentTokenInfo() = default;

PaymentTokenInfo::PaymentTokenInfo(const PaymentTokenInfo& other) = default;

PaymentTokenInfo& PaymentTokenInfo::operator=(const PaymentTokenInfo& other) =
    default;

PaymentTokenInfo::PaymentTokenInfo(PaymentTokenInfo&& other) noexcept = default;

PaymentTokenInfo& PaymentTokenInfo::operator=(
    PaymentTokenInfo&& other) noexcept = default;

PaymentTokenInfo::~PaymentTokenInfo() = default;

bool PaymentTokenInfo::IsValid() const {
  return !transaction_id.empty() && unblinded_token.has_value() &&
         public_key.has_value() &&
         confirmation_type != mojom::ConfirmationType::kUndefined &&
         ad_type != mojom::AdType::kUndefined;
}

}  // namespace catsxp_ads
