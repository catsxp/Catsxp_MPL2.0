/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_util.h"

#include <optional>
#include <string>
#include <string_view>

#include "base/base64url.h"
#include "base/check.h"
#include "base/json/json_reader.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/confirmation_payload_json_writer.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kVerificationSignatureKey = "signature";

bool Verify(const ConfirmationInfo& confirmation) {
  CHECK(confirmation.reward);

  std::optional<cbr::VerificationKey> verification_key =
      confirmation.reward->unblinded_token.DeriveVerificationKey();
  if (!verification_key) {
    return false;
  }

  std::string credential;
  if (!base::Base64UrlDecode(confirmation.reward->credential_base64url,
                             base::Base64UrlDecodePolicy::REQUIRE_PADDING,
                             &credential)) {
    return false;
  }

  std::optional<base::DictValue> dict =
      base::JSONReader::ReadDict(credential, base::JSON_PARSE_RFC);
  if (!dict) {
    return false;
  }

  if (const auto* const value = dict->FindString(kVerificationSignatureKey)) {
    const cbr::VerificationSignature verification_signature =
        cbr::VerificationSignature(*value);
    if (!verification_signature.has_value()) {
      return false;
    }

    return verification_key->Verify(
        verification_signature,
        json::writer::WriteConfirmationPayload(confirmation));
  }

  return false;
}

}  // namespace

bool IsValid(const ConfirmationInfo& confirmation) {
  if (confirmation.transaction_id.empty() ||
      confirmation.creative_instance_id.empty() ||
      confirmation.type == mojom::ConfirmationType::kUndefined ||
      confirmation.ad_type == mojom::AdType::kUndefined ||
      !confirmation.created_at) {
    return false;
  }

  if (!confirmation.reward) {
    return true;
  }

  if (!confirmation.reward->IsValid()) {
    return false;
  }

  return Verify(confirmation);
}

}  // namespace catsxp_ads
