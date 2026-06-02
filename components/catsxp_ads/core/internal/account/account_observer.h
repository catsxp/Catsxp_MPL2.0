/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct TransactionInfo;
struct WalletInfo;

class AccountObserver : public base::CheckedObserver {
 public:
  // Invoked when the `wallet` did initialize.
  virtual void OnDidInitializeWallet(const WalletInfo& wallet) {}

  // Invoked if the wallet is invalid.
  virtual void OnFailedToInitializeWallet() {}

  // Invoked after successfully processing a deposit for `transaction`.
  virtual void OnDidProcessDeposit(const TransactionInfo& transaction) {}

  // Invoked after failing to process a deposit for `creative_instance_id`,
  // `mojom_ad_type` and `mojom_confirmation_type`.
  virtual void OnFailedToProcessDeposit(
      const std::string& creative_instance_id,
      mojom::AdType mojom_ad_type,
      mojom::ConfirmationType mojom_confirmation_type) {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_
