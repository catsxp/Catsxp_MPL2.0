/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"

namespace catsxp_ads {

bool ConfirmationTokenInfo::IsValid() const {
  return unblinded_token.has_value() && public_key.has_value() &&
         !signature_base64.empty();
}

}  // namespace catsxp_ads
