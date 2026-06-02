/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_util.h"

#include <vector>

#include "base/base64.h"
#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/crypto/crypto_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/crypto/key_pair_info.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

std::optional<WalletInfo> MaybeBuildWalletFromRecoverySeed(
    const std::string& payment_id,
    const std::string& recovery_seed_base64) {
  std::optional<std::vector<uint8_t>> recovery_seed =
      base::Base64Decode(recovery_seed_base64);
  if (!recovery_seed) {
    return std::nullopt;
  }

  std::optional<crypto::KeyPairInfo> key_pair =
      crypto::GenerateSignKeyPairFromSeed(*recovery_seed);
  crypto::SecureZero(*recovery_seed);
  if (!key_pair || !key_pair->IsValid()) {
    return std::nullopt;
  }

  WalletInfo wallet{
      .payment_id = payment_id,
      .public_key_base64 = base::Base64Encode(key_pair->public_key),
      .secret_key_base64 = base::Base64Encode(key_pair->secret_key)};
  crypto::SecureZero(key_pair->secret_key);

  if (!wallet.IsValid()) {
    return std::nullopt;
  }

  return wallet;
}

std::optional<WalletInfo> MaybeBuildWalletFromRecoverySeed(
    const mojom::WalletInfo* const mojom_wallet) {
  CHECK(mojom_wallet);

  return MaybeBuildWalletFromRecoverySeed(mojom_wallet->payment_id,
                                          mojom_wallet->recovery_seed_base64);
}

}  // namespace catsxp_ads
