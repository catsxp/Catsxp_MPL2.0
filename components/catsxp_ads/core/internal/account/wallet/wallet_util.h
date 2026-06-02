/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_

#include <optional>
#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct WalletInfo;

std::optional<WalletInfo> MaybeBuildWalletFromRecoverySeed(
    const std::string& payment_id,
    const std::string& recovery_seed_base64);

std::optional<WalletInfo> MaybeBuildWalletFromRecoverySeed(
    const mojom::WalletInfo* mojom_wallet);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_
