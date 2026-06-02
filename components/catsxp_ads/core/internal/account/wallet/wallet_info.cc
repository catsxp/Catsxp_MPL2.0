/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"

#include "catsxp/components/catsxp_ads/core/internal/common/crypto/crypto_util.h"

namespace catsxp_ads {

WalletInfo::~WalletInfo() {
  crypto::SecureZero(payment_id);
  crypto::SecureZero(public_key_base64);
  crypto::SecureZero(secret_key_base64);
}

bool WalletInfo::IsValid() const {
  return !payment_id.empty() && !public_key_base64.empty() &&
         !secret_key_base64.empty();
}

}  // namespace catsxp_ads
