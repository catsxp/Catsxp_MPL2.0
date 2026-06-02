/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct WalletInfo;

namespace test {

WalletInfo Wallet();
mojom::WalletInfoPtr MojomWallet();
mojom::WalletInfoPtr InvalidMojomWallet();

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_TEST_WALLET_TEST_UTIL_H_
