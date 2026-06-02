/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_PREIMAGE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_PREIMAGE_TEST_UTIL_H_

#include <string>
#include <vector>

namespace catsxp_ads::cbr {

class TokenPreimage;

namespace test {

TokenPreimage GetTokenPreimage();
TokenPreimage GetInvalidTokenPreimage();

const std::vector<std::string>& GetTokenPreimages();

}  // namespace test

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_TOKEN_PREIMAGE_TEST_UTIL_H_
