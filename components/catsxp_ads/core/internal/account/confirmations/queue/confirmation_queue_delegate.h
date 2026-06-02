/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DELEGATE_H_

#include "base/time/time.h"

namespace catsxp_ads {

struct ConfirmationInfo;

class ConfirmationQueueDelegate {
 public:
  // Invoked to tell the delegate that we added a confirmation to the queue.
  virtual void OnDidAddConfirmationToQueue(
      const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that we failed to add a confirmation to the
  // queue.
  virtual void OnFailedToAddConfirmationToQueue(
      const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that we will process the confirmation queue.
  virtual void OnWillProcessConfirmationQueue(
      const ConfirmationInfo& confirmation,
      base::Time process_at) {}

  // Invoked to tell the delegate that we processed the confirmation queue.
  virtual void OnDidProcessConfirmationQueue(
      const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that we failed to process the confirmation
  // queue.
  virtual void OnFailedToProcessConfirmationQueue(
      const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that we failed to process the next
  // confirmation.
  virtual void OnFailedToProcessNextConfirmationInQueue() {}

  // Invoked to tell the delegate that the confirmation queue has been
  // exhausted.
  virtual void OnDidExhaustConfirmationQueue() {}

 protected:
  virtual ~ConfirmationQueueDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_CONFIRMATION_QUEUE_DELEGATE_H_
