/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/reward_confirmation_payload_util.h"

#include <optional>
#include <string>
#include <string_view>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_info.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kBlindedTokensKey = "blindedPaymentTokens";
constexpr std::string_view kPublicKeyKey = "publicKey";

}  // namespace

base::DictValue BuildRewardConfirmationPayload(const RewardInfo& reward) {
  std::optional<std::string> blinded_token_base64 =
      reward.blinded_token.EncodeBase64();
  CHECK(blinded_token_base64);

  std::optional<std::string> public_key_base64 =
      reward.public_key.EncodeBase64();
  CHECK(public_key_base64);

  return base::DictValue()
      .Set(kBlindedTokensKey, base::ListValue().Append(*blinded_token_base64))
      .Set(kPublicKeyKey, *public_key_base64);
}

}  // namespace catsxp_ads
