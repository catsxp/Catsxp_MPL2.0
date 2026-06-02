/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_TEST_CONFIRMATION_QUEUE_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_TEST_CONFIRMATION_QUEUE_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/queue/confirmation_queue_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class ConfirmationQueueDelegateMock : public ConfirmationQueueDelegate {
 public:
  ConfirmationQueueDelegateMock();

  ConfirmationQueueDelegateMock(const ConfirmationQueueDelegateMock&) = delete;
  ConfirmationQueueDelegateMock& operator=(
      const ConfirmationQueueDelegateMock&) = delete;

  ~ConfirmationQueueDelegateMock() override;

  MOCK_METHOD(void, OnDidAddConfirmationToQueue, (const ConfirmationInfo&));
  MOCK_METHOD(void,
              OnFailedToAddConfirmationToQueue,
              (const ConfirmationInfo&));

  MOCK_METHOD(void,
              OnWillProcessConfirmationQueue,
              (const ConfirmationInfo&, base::Time));
  MOCK_METHOD(void, OnDidProcessConfirmationQueue, (const ConfirmationInfo&));
  MOCK_METHOD(void,
              OnFailedToProcessConfirmationQueue,
              (const ConfirmationInfo&));
  MOCK_METHOD(void, OnFailedToProcessNextConfirmationInQueue, ());

  MOCK_METHOD(void, OnDidExhaustConfirmationQueue, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_QUEUE_TEST_CONFIRMATION_QUEUE_DELEGATE_MOCK_H_
