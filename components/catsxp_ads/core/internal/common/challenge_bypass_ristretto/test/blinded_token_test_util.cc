/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/blinded_token_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"

namespace catsxp_ads::cbr::test {

BlindedToken GetBlindedToken() {
  return BlindedToken(kBlindedTokenBase64);
}

BlindedToken GetInvalidBlindedToken() {
  return BlindedToken(kInvalidBase64);
}

BlindedTokenList GetBlindedTokens() {
  return {GetBlindedToken()};
}

BlindedTokenList GetInvalidBlindedTokens() {
  return {GetInvalidBlindedToken()};
}

}  // namespace catsxp_ads::cbr::test
