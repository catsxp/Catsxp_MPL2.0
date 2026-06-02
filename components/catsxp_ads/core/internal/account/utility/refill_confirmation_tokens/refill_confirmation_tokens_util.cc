/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_util.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_feature.h"

namespace catsxp_ads {

bool ShouldRefillConfirmationTokens() {
  return ConfirmationTokenCount() < kMinConfirmationTokens.Get();
}

size_t CalculateAmountOfConfirmationTokensToRefill() {
  return kMaxConfirmationTokens.Get() - ConfirmationTokenCount();
}

}  // namespace catsxp_ads
