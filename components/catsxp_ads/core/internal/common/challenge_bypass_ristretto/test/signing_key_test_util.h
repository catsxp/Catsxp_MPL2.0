/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_SIGNING_KEY_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_SIGNING_KEY_TEST_UTIL_H_

namespace catsxp_ads::cbr {

class SigningKey;

namespace test {

SigningKey GetSigningKey();
SigningKey GetInvalidSigningKey();

}  // namespace test

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_SIGNING_KEY_TEST_UTIL_H_
