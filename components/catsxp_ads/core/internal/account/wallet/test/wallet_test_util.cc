/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/test/wallet_test_util.h"

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/test/wallet_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

WalletInfo Wallet() {
  std::optional<WalletInfo> wallet = MaybeBuildWalletFromRecoverySeed(
      kWalletPaymentId, kWalletRecoverySeedBase64);
  CHECK(wallet);

  return *wallet;
}

mojom::WalletInfoPtr MojomWallet() {
  mojom::WalletInfoPtr mojom_wallet = mojom::WalletInfo::New();
  mojom_wallet->payment_id = kWalletPaymentId;
  mojom_wallet->recovery_seed_base64 = kWalletRecoverySeedBase64;
  return mojom_wallet;
}

mojom::WalletInfoPtr InvalidMojomWallet() {
  mojom::WalletInfoPtr mojom_wallet = mojom::WalletInfo::New();
  mojom_wallet->payment_id = kWalletPaymentId;
  mojom_wallet->recovery_seed_base64 = kInvalidWalletRecoverySeed;
  return mojom_wallet;
}

}  // namespace catsxp_ads::test
