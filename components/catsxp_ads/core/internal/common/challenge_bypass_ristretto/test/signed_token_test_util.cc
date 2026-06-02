/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/signed_token_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"

namespace catsxp_ads::cbr::test {

SignedToken GetSignedToken() {
  return SignedToken(kSignedTokenBase64);
}

SignedToken GetInvalidSignedToken() {
  return SignedToken(kInvalidBase64);
}

SignedTokenList GetSignedTokens() {
  return {GetSignedToken()};
}

SignedTokenList GetInvalidSignedTokens() {
  return {GetInvalidSignedToken()};
}

}  // namespace catsxp_ads::cbr::test
