/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_VERIFICATION_SIGNATURE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_VERIFICATION_SIGNATURE_TEST_UTIL_H_

namespace catsxp_ads::cbr {

class VerificationSignature;

namespace test {

VerificationSignature GetVerificationSignature();
VerificationSignature GetInvalidVerificationSignature();

}  // namespace test

}  // namespace catsxp_ads::cbr

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_CHALLENGE_BYPASS_RISTRETTO_TEST_VERIFICATION_SIGNATURE_TEST_UTIL_H_
