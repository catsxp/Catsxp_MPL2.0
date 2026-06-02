/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_NON_REWARD_REDEEM_NON_REWARD_CONFIRMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_NON_REWARD_REDEEM_NON_REWARD_CONFIRMATION_H_

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct ConfirmationInfo;

class RedeemNonRewardConfirmation final {
 public:
  RedeemNonRewardConfirmation(const RedeemNonRewardConfirmation&) = delete;
  RedeemNonRewardConfirmation& operator=(const RedeemNonRewardConfirmation&) =
      delete;

  RedeemNonRewardConfirmation(RedeemNonRewardConfirmation&&) noexcept;
  RedeemNonRewardConfirmation& operator=(
      RedeemNonRewardConfirmation&&) noexcept;

  ~RedeemNonRewardConfirmation();

  static void CreateAndRedeem(
      base::WeakPtr<RedeemConfirmationDelegate> delegate,
      const ConfirmationInfo& confirmation);

 private:
  explicit RedeemNonRewardConfirmation(
      base::WeakPtr<RedeemConfirmationDelegate> delegate);

  static void Redeem(RedeemNonRewardConfirmation redeem_confirmation,
                     const ConfirmationInfo& confirmation);

  static void CreateConfirmation(
      RedeemNonRewardConfirmation redeem_confirmation,
      const ConfirmationInfo& confirmation);
  static void CreateConfirmationCallback(
      RedeemNonRewardConfirmation redeem_confirmation,
      const ConfirmationInfo& confirmation,
      const mojom::UrlResponseInfo& mojom_url_response);

  void SuccessfullyRedeemedConfirmation(const ConfirmationInfo& confirmation);
  void FailedToRedeemConfirmation(const ConfirmationInfo& confirmation,
                                  bool should_retry);

  void NotifyDidRedeemConfirmation(const ConfirmationInfo& confirmation) const;
  void NotifyFailedToRedeemConfirmation(const ConfirmationInfo& confirmation,
                                        bool should_retry) const;

  base::WeakPtr<RedeemConfirmationDelegate> delegate_ = nullptr;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_NON_REWARD_REDEEM_NON_REWARD_CONFIRMATION_H_
