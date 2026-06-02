/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/credential_builder.h"

#include <string_view>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token_preimage.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_signature.h"

namespace catsxp_ads::cbr {

namespace {

constexpr std::string_view kVerificationSignatureKey = "signature";
constexpr std::string_view kTokenPreimageKey = "t";

}  // namespace

std::optional<base::DictValue> MaybeBuildCredential(
    const UnblindedToken& unblinded_token,
    const std::string& payload) {
  CHECK(unblinded_token.has_value());
  CHECK(!payload.empty());

  std::optional<VerificationKey> verification_key =
      unblinded_token.DeriveVerificationKey();
  if (!verification_key) {
    return std::nullopt;
  }

  std::optional<VerificationSignature> verification_signature =
      verification_key->Sign(payload);
  if (!verification_signature) {
    return std::nullopt;
  }

  std::optional<std::string> verification_signature_base64 =
      verification_signature->EncodeBase64();
  if (!verification_signature_base64) {
    return std::nullopt;
  }

  std::optional<TokenPreimage> token_preimage =
      unblinded_token.GetTokenPreimage();
  if (!token_preimage) {
    return std::nullopt;
  }

  std::optional<std::string> token_preimage_base64 =
      token_preimage->EncodeBase64();
  if (!token_preimage_base64) {
    return std::nullopt;
  }

  return base::DictValue()
      .Set(kVerificationSignatureKey, *verification_signature_base64)
      .Set(kTokenPreimageKey, *token_preimage_base64);
}

}  // namespace catsxp_ads::cbr
