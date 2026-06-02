/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"

namespace catsxp_ads {

class PaymentTokens final {
 public:
  PaymentTokens();

  PaymentTokens(const PaymentTokens&) = delete;
  PaymentTokens& operator=(const PaymentTokens&) = delete;

  ~PaymentTokens();

  const PaymentTokenList& GetAllTokens() const;

  void SetTokens(const PaymentTokenList& payment_tokens);

  void AddTokens(const PaymentTokenList& payment_tokens);

  void RemoveTokens(const PaymentTokenList& payment_tokens);

  bool TokenExists(const PaymentTokenInfo& payment_token) const;

  size_t Count() const;

  bool IsEmpty() const;

 private:
  PaymentTokenList payment_tokens_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_PAYMENT_TOKENS_PAYMENT_TOKENS_H_
