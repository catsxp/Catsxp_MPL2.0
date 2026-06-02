/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_H_

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace catsxp_ads {

class ConfirmationTokens final {
 public:
  ConfirmationTokens();

  ConfirmationTokens(const ConfirmationTokens&) = delete;
  ConfirmationTokens& operator=(const ConfirmationTokens&) = delete;

  ~ConfirmationTokens();

  const ConfirmationTokenInfo& Get() const;
  const ConfirmationTokenList& GetAll() const;

  void Set(const ConfirmationTokenList& confirmation_tokens);

  void Add(const ConfirmationTokenList& confirmation_tokens);

  bool Remove(const ConfirmationTokenInfo& confirmation_token);

  bool Exists(const ConfirmationTokenInfo& confirmation_token) const;

  size_t Count() const;

  bool IsEmpty() const;

 private:
  ConfirmationTokenList confirmation_tokens_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TOKENS_CONFIRMATION_TOKENS_CONFIRMATION_TOKENS_H_
