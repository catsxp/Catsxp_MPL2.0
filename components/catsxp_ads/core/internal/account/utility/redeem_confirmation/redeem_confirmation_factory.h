/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_FACTORY_H_

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"

namespace catsxp_ads {

struct ConfirmationInfo;

class RedeemConfirmationFactory final {
 public:
  // This class contains only static methods.
  RedeemConfirmationFactory() = delete;
  RedeemConfirmationFactory(const RedeemConfirmationFactory&) = delete;
  RedeemConfirmationFactory& operator=(const RedeemConfirmationFactory&) =
      delete;

  static void BuildAndRedeemConfirmation(
      base::WeakPtr<RedeemConfirmationDelegate> delegate,
      const ConfirmationInfo& confirmation);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_FACTORY_H_
