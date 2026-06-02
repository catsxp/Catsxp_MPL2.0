/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signing_key_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signing_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"

namespace catsxp_ads::cbr::test {

SigningKey GetSigningKey() {
  return SigningKey(kSigningKeyBase64);
}

SigningKey GetInvalidSigningKey() {
  return SigningKey(kInvalidBase64);
}

}  // namespace catsxp_ads::cbr::test
