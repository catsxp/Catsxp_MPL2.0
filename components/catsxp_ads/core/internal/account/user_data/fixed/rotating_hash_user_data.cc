/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data.h"

#include <optional>
#include <string>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kRotatingHashKey = "rotatingHash";
}  // namespace

base::DictValue BuildRotatingHashUserData(const TransactionInfo& transaction) {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  std::optional<std::string> rotating_hash = BuildRotatingHash(transaction);
  if (!rotating_hash) {
    // Invalid rotating hash.
    return {};
  }

  return base::DictValue().Set(kRotatingHashKey, *rotating_hash);
}

}  // namespace catsxp_ads
