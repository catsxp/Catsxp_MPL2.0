/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/get_signed_tokens_url_request_util.h"

#include "base/test/values_test_util.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/test/wallet_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/public_key_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/unblinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsGetSignedTokensUrlRequestUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsGetSignedTokensUrlRequestUtilTest, ParseCaptchaId) {
  // Arrange
  const base::DictValue dict = base::test::ParseJsonDict(
      R"JSON(
          {
            "captcha_id": "daf85dc8-164e-4eb9-a4d4-1836055004b3"
          })JSON");

  // Act & Assert
  EXPECT_EQ("daf85dc8-164e-4eb9-a4d4-1836055004b3", ParseCaptchaId(dict));
}

TEST_F(CatsxpAdsGetSignedTokensUrlRequestUtilTest, DoNotParseMissingCaptchaId) {
  // Act & Assert
  EXPECT_FALSE(ParseCaptchaId({}));
}

TEST_F(CatsxpAdsGetSignedTokensUrlRequestUtilTest,
       BuildAndAddConfirmationTokens) {
  // Act
  BuildAndAddConfirmationTokens(cbr::test::GetUnblindedTokens(),
                                cbr::test::GetPublicKey(), test::Wallet());

  // Assert
  EXPECT_FALSE(GetConfirmationTokens().IsEmpty());
}

}  // namespace catsxp_ads
