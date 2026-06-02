/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/created_at_timestamp_user_data.h"

#include <string_view>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kCreatedAtTimestampKey = "createdAtTimestamp";
}  // namespace

base::DictValue BuildCreatedAtTimestampUserData(
    const TransactionInfo& transaction) {
  CHECK(transaction.IsValid());

  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  return base::DictValue().Set(
      kCreatedAtTimestampKey,
      TimeToPrivacyPreservingIso8601(*transaction.created_at));
}

}  // namespace catsxp_ads
