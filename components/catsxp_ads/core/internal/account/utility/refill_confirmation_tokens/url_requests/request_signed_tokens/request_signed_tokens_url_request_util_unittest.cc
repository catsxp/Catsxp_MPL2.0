/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/request_signed_tokens/request_signed_tokens_url_request_util.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/test/refill_confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/test/get_signed_tokens_url_request_builder_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRequestSignedTokensUrlRequestUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRequestSignedTokensUrlRequestUtilTest, ParseNonce) {
  // Act & Assert
  EXPECT_EQ(test::kRequestSignedTokensNonce,
            ParseNonce(base::test::ParseJsonDict(
                test::BuildRequestSignedTokensUrlResponseBody())));
}

TEST_F(CatsxpAdsRequestSignedTokensUrlRequestUtilTest, DoNotParseMissingNonce) {
  // Act & Assert
  EXPECT_FALSE(ParseNonce({}));
}

}  // namespace catsxp_ads
