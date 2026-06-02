/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/verification_key_test_util.h"

#include <optional>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/unblinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/verification_key.h"

namespace catsxp_ads::cbr::test {

VerificationKey GetVerificationKey() {
  const UnblindedToken unblinded_token = GetUnblindedToken();
  std::optional<VerificationKey> verification_key =
      unblinded_token.DeriveVerificationKey();
  CHECK(verification_key);
  return *verification_key;
}

}  // namespace catsxp_ads::cbr::test
