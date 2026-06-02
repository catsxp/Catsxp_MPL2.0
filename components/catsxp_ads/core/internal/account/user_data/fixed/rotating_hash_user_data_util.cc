/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data_util.h"

#include <cstdint>
#include <vector>

#include "base/base64.h"
#include "base/strings/strcat.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/account/transactions/transaction_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/crypto/crypto_util.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

std::optional<std::string> BuildRotatingHash(
    const TransactionInfo& transaction) {
  const std::string& device_id =
      GlobalState::GetInstance()->SysInfo().device_id;
  if (device_id.empty()) {
    return std::nullopt;
  }

  const std::string hours = base::NumberToString(
      base::Time::Now().ToDeltaSinceWindowsEpoch().InHours());

  const std::string rotating_hash =
      base::StrCat({device_id, transaction.creative_instance_id, hours});

  const std::vector<uint8_t> rotating_hash_sha256 =
      crypto::Sha256(rotating_hash);

  return base::Base64Encode(rotating_hash_sha256);
}

}  // namespace catsxp_ads
