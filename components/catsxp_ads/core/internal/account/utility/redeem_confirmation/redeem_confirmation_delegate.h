/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_H_

namespace catsxp_ads {

struct ConfirmationInfo;

class RedeemConfirmationDelegate {
 public:
  // Invoked to tell the delegate that the `confirmation` was redeemed.
  virtual void OnDidRedeemConfirmation(const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that `confirmation` redemption failed.
  virtual void OnFailedToRedeemConfirmation(
      const ConfirmationInfo& confirmation,
      bool should_retry) {}

 protected:
  virtual ~RedeemConfirmationDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REDEEM_CONFIRMATION_DELEGATE_H_
