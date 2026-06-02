/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_

#include <string>

namespace catsxp_ads {

struct WalletInfo final {
  bool operator==(const WalletInfo&) const = default;

  ~WalletInfo();

  [[nodiscard]] bool IsValid() const;

  std::string payment_id;
  std::string public_key_base64;
  std::string secret_key_base64;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_
