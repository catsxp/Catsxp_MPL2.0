/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_TEST_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"

namespace catsxp_ads {

struct IssuersInfo;

namespace test {

TokenIssuerList BuildTokenIssuers();

std::string BuildIssuersUrlResponseBody();

IssuersInfo BuildIssuers(
    int ping,
    const TokenIssuerPublicKeyMap& confirmation_token_issuer_public_keys,
    const TokenIssuerPublicKeyMap& payment_token_issuer_public_keys);
IssuersInfo BuildIssuers();

void BuildAndSetIssuers();

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_TEST_ISSUERS_TEST_UTIL_H_
