/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_INFO_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"

namespace catsxp_ads {

struct RewardInfo final {
  RewardInfo();

  RewardInfo(const RewardInfo&);
  RewardInfo& operator=(const RewardInfo&);

  RewardInfo(RewardInfo&&) noexcept;
  RewardInfo& operator=(RewardInfo&&) noexcept;

  ~RewardInfo();

  bool operator==(const RewardInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  cbr::Token token;
  cbr::BlindedToken blinded_token;
  cbr::UnblindedToken unblinded_token;
  cbr::PublicKey public_key;
  std::string signature;
  std::string credential_base64url;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_INFO_H_
