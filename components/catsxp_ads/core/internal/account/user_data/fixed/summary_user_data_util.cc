/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/summary_user_data_util.h"

namespace catsxp_ads {

AdTypeBucketMap BuildAdTypeBuckets(const PaymentTokenList& payment_tokens) {
  AdTypeBucketMap buckets;

  for (const auto& payment_token : payment_tokens) {
    ++buckets[payment_token.ad_type][payment_token.confirmation_type];
  }

  return buckets;
}

}  // namespace catsxp_ads
