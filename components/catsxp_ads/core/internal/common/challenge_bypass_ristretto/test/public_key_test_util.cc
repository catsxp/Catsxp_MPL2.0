/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/public_key_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"

namespace catsxp_ads::cbr::test {

PublicKey GetPublicKey() {
  return PublicKey(kPublicKeyBase64);
}

PublicKey GetMismatchingPublicKey() {
  return {};
}

PublicKey GetInvalidPublicKey() {
  return PublicKey(kInvalidBase64);
}

}  // namespace catsxp_ads::cbr::test
