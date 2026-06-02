/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TEST_ACCOUNT_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TEST_ACCOUNT_OBSERVER_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/account_observer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class AccountObserverMock : public AccountObserver {
 public:
  AccountObserverMock();

  AccountObserverMock(const AccountObserverMock&) = delete;
  AccountObserverMock& operator=(const AccountObserverMock&) = delete;

  ~AccountObserverMock() override;

  MOCK_METHOD(void, OnDidInitializeWallet, (const WalletInfo&));

  MOCK_METHOD(void, OnFailedToInitializeWallet, ());

  MOCK_METHOD(void, OnDidProcessDeposit, (const TransactionInfo&));

  MOCK_METHOD(void,
              OnFailedToProcessDeposit,
              (const std::string&, mojom::AdType, mojom::ConfirmationType));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_TEST_ACCOUNT_OBSERVER_MOCK_H_
