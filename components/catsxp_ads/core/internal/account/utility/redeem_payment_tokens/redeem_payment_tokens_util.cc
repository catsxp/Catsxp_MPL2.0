/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_util.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/debug/debug_flag_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/random/random_util.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"

namespace catsxp_ads {

namespace {

constexpr base::TimeDelta kDebugRedeemPaymentTokensAfter = base::Minutes(2);
constexpr base::TimeDelta kMinimumDelayBeforeRedeemingTokens = base::Minutes(1);

base::Time NextTokenRedemptionAt() {
  return GetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt);
}

bool HasPreviouslyRedeemedTokens() {
  return !NextTokenRedemptionAt().is_null();
}

bool ShouldHaveRedeemedTokensInThePast() {
  return NextTokenRedemptionAt() < base::Time::Now();
}

}  // namespace

void SetNextTokenRedemptionAt(base::Time next_payment_token_redemption_at) {
  SetProfileTimePref(prefs::kNextPaymentTokenRedemptionAt,
                     next_payment_token_redemption_at);
}

base::Time ScheduleNextTokenRedemptionAt() {
  return base::Time::Now() +
         (ShouldDebug()
              ? kDebugRedeemPaymentTokensAfter
              : RandTimeDeltaWithJitter(kRedeemPaymentTokensAfter.Get()));
}

base::TimeDelta CalculateDelayBeforeRedeemingTokens() {
  if (!HasPreviouslyRedeemedTokens()) {
    return ScheduleNextTokenRedemptionAt() - base::Time::Now();
  }

  if (ShouldHaveRedeemedTokensInThePast()) {
    return kMinimumDelayBeforeRedeemingTokens;
  }

  const base::TimeDelta delay = NextTokenRedemptionAt() - base::Time::Now();
  if (delay < kMinimumDelayBeforeRedeemingTokens) {
    return kMinimumDelayBeforeRedeemingTokens;
  }

  return delay;
}

}  // namespace catsxp_ads
