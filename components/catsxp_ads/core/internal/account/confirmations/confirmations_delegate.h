/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_H_

namespace catsxp_ads {

struct ConfirmationInfo;

class ConfirmationDelegate {
 public:
  // Invoked to tell the delegate that the `confirmation` was successfully sent.
  virtual void OnDidConfirm(const ConfirmationInfo& confirmation) {}

  // Invoked to tell the delegate that the `confirmation` failed to send.
  virtual void OnFailedToConfirm(const ConfirmationInfo& confirmation) {}

 protected:
  virtual ~ConfirmationDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATIONS_DELEGATE_H_
