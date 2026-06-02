/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/segment_user_data.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kSegmentKey = "segment";
}  // namespace

base::DictValue BuildSegmentUserData(const TransactionInfo& transaction) {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  if (transaction.ad_type == mojom::AdType::kSearchResultAd) {
    // Unsupported ad type.
    return {};
  }

  if (transaction.segment.empty()) {
    // Invalid segment.
    return {};
  }

  return base::DictValue().Set(kSegmentKey, transaction.segment);
}

}  // namespace catsxp_ads
