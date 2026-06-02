/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_H_

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/confirmation_queue.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/confirmation_queue_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"

namespace catsxp_ads {

struct TransactionInfo;

class Confirmations final : public ConfirmationQueueDelegate,
                            public RedeemConfirmationDelegate {
 public:
  Confirmations();

  Confirmations(const Confirmations&) = delete;
  Confirmations& operator=(const Confirmations&) = delete;

  ~Confirmations() override;

  void SetDelegate(ConfirmationDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void Confirm(const TransactionInfo& transaction, base::DictValue user_data);

 private:
  void NotifyDidConfirm(const ConfirmationInfo& confirmation) const;
  void NotifyFailedToConfirm(const ConfirmationInfo& confirmation) const;

  // ConfirmationQueueDelegate:
  void OnDidAddConfirmationToQueue(
      const ConfirmationInfo& confirmation) override;
  void OnWillProcessConfirmationQueue(const ConfirmationInfo& confirmation,
                                      base::Time process_at) override;
  void OnDidProcessConfirmationQueue(
      const ConfirmationInfo& confirmation) override;
  void OnFailedToProcessConfirmationQueue(
      const ConfirmationInfo& confirmation) override;
  void OnDidExhaustConfirmationQueue() override;

  raw_ptr<ConfirmationDelegate> delegate_ = nullptr;  // Not owned.

  ConfirmationQueue confirmation_queue_;

  base::WeakPtrFactory<Confirmations> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_H_
