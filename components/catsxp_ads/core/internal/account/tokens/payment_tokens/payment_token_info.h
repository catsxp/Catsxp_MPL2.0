/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_INFO_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"

namespace catsxp_ads {

struct PaymentTokenInfo final {
  PaymentTokenInfo();

  PaymentTokenInfo(const PaymentTokenInfo&);
  PaymentTokenInfo& operator=(const PaymentTokenInfo&);

  PaymentTokenInfo(PaymentTokenInfo&&) noexcept;
  PaymentTokenInfo& operator=(PaymentTokenInfo&&) noexcept;

  ~PaymentTokenInfo();

  bool operator==(const PaymentTokenInfo&) const = default;

  // Returns true if all fields have valid values.
  [[nodiscard]] bool IsValid() const;

  std::string transaction_id;
  cbr::UnblindedToken unblinded_token;
  cbr::PublicKey public_key;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  mojom::AdType ad_type = mojom::AdType::kUndefined;
};

using PaymentTokenList = std::vector<PaymentTokenInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKEN_INFO_H_
