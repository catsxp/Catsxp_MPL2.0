/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_credential_json_writer.h"

#include "base/check.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/credential_builder.h"

namespace catsxp_ads::json::writer {

std::optional<std::string> WriteRewardCredential(
    base::optional_ref<const RewardInfo> reward,
    const std::string& payload) {
  CHECK(!payload.empty());

  if (!reward) {
    return std::nullopt;
  }

  std::optional<base::DictValue> credential =
      cbr::MaybeBuildCredential(reward->unblinded_token, payload);
  if (!credential) {
    return std::nullopt;
  }

  std::string json;
  CHECK(base::JSONWriter::Write(*credential, &json));
  return json;
}

}  // namespace catsxp_ads::json::writer
