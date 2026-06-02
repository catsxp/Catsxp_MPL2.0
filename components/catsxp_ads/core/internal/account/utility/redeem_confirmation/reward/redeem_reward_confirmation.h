/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_REDEEM_REWARD_CONFIRMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_REDEEM_REWARD_CONFIRMATION_H_

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/redeem_confirmation_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/url_response_result.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct ConfirmationInfo;
struct PaymentTokenInfo;

class RedeemRewardConfirmation final {
 public:
  RedeemRewardConfirmation(const RedeemRewardConfirmation&) = delete;
  RedeemRewardConfirmation& operator=(const RedeemRewardConfirmation&) = delete;

  RedeemRewardConfirmation(RedeemRewardConfirmation&&) noexcept;
  RedeemRewardConfirmation& operator=(RedeemRewardConfirmation&&) noexcept;

  ~RedeemRewardConfirmation();

  static void CreateAndRedeem(
      base::WeakPtr<RedeemConfirmationDelegate> delegate,
      const ConfirmationInfo& confirmation);

 private:
  explicit RedeemRewardConfirmation(
      base::WeakPtr<RedeemConfirmationDelegate> delegate);

  static void Redeem(RedeemRewardConfirmation redeem_confirmation,
                     const ConfirmationInfo& confirmation);

  static void CreateConfirmation(RedeemRewardConfirmation redeem_confirmation,
                                 const ConfirmationInfo& confirmation);
  static void CreateConfirmationCallback(
      RedeemRewardConfirmation redeem_confirmation,
      const ConfirmationInfo& confirmation,
      const mojom::UrlResponseInfo& mojom_url_response);
  static UrlResponseResult<void> HandleCreateConfirmationUrlResponse(
      const mojom::UrlResponseInfo& mojom_url_response);

  static void FetchPaymentTokenAfter(
      base::TimeDelta delay,
      RedeemRewardConfirmation redeem_confirmation,
      const ConfirmationInfo& confirmation);
  static void FetchPaymentToken(RedeemRewardConfirmation redeem_confirmation,
                                const ConfirmationInfo& confirmation);
  static void FetchPaymentTokenCallback(
      RedeemRewardConfirmation redeem_confirmation,
      const ConfirmationInfo& confirmation,
      const mojom::UrlResponseInfo& mojom_url_response);
  static UrlResponseResult<PaymentTokenInfo> HandleFetchPaymentTokenUrlResponse(
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

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_REDEEM_REWARD_CONFIRMATION_H_
