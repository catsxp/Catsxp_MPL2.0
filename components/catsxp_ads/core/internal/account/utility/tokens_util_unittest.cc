/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/tokens_util.h"

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/public_key.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/signed_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/blinded_token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/public_key_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/token_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/token.h"  // IWYU pragma: keep
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

base::DictValue BuildUrlResponseBody() {
  return base::DictValue()
      .Set("batchProof", cbr::test::kBatchDLEQProofBase64)
      .Set("signedTokens",
           base::ListValue().Append(cbr::test::kSignedTokenBase64))
      .Set("publicKey", cbr::test::kPublicKeyBase64);
}

}  // namespace

class CatsxpAdsSignedTokensUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsSignedTokensUtilTest, ParsePublicKey) {
  // Act & Assert
  EXPECT_EQ(cbr::PublicKey(cbr::test::kPublicKeyBase64),
            ParsePublicKey(BuildUrlResponseBody()));
}

TEST_F(CatsxpAdsSignedTokensUtilTest, DoNotParseInvalidPublicKey) {
  // Arrange
  const base::DictValue dict =
      BuildUrlResponseBody().Set("publicKey", cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(ParsePublicKey(dict));
}

TEST_F(CatsxpAdsSignedTokensUtilTest, ParseSignedTokens) {
  // Act
  std::optional<cbr::SignedTokenList> signed_tokens =
      ParseSignedTokens(BuildUrlResponseBody());
  ASSERT_TRUE(signed_tokens);

  // Assert
  const cbr::SignedTokenList expected_signed_tokens = {
      cbr::SignedToken(cbr::test::kSignedTokenBase64)};
  EXPECT_EQ(expected_signed_tokens, signed_tokens);
}

TEST_F(CatsxpAdsSignedTokensUtilTest, DoNotParseSignedTokensIfMissingKey) {
  // Arrange
  base::DictValue dict = BuildUrlResponseBody();
  dict.Remove("signedTokens");

  // Act & Assert
  EXPECT_FALSE(ParseSignedTokens(dict));
}

TEST_F(CatsxpAdsSignedTokensUtilTest, DoNotParseInvalidSignedTokens) {
  // Arrange
  const base::DictValue dict =
      BuildUrlResponseBody().Set("signedTokens", cbr::test::kInvalidBase64);

  // Act & Assert
  EXPECT_FALSE(ParseSignedTokens(dict));
}

TEST_F(CatsxpAdsSignedTokensUtilTest, ParseVerifyAndUnblindTokens) {
  // Arrange
  test::BuildAndSetIssuers();

  // Act
  const auto result = ParseVerifyAndUnblindTokens(
      BuildUrlResponseBody(), cbr::test::GetTokens(),
      cbr::test::GetBlindedTokens(), cbr::test::GetPublicKey());

  // Assert
  EXPECT_TRUE(result.has_value());
}

TEST_F(CatsxpAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindTokensIfMissingBatchDLEQProof) {
  // Arrange
  base::DictValue dict = BuildUrlResponseBody();
  dict.Remove("batchProof");

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(CatsxpAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindMissingSignedTokens) {
  // Arrange
  base::DictValue dict = BuildUrlResponseBody();
  dict.Remove("signedTokens");

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(CatsxpAdsSignedTokensUtilTest,
       DoNoParseVerifyAndUnblindMalformedSignedTokens) {
  // Arrange
  const base::DictValue dict = BuildUrlResponseBody().Set(
      "signedTokens", base::ListValue().Append(/*invalid*/ 0));

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

TEST_F(CatsxpAdsSignedTokensUtilTest,
       DoNotParseVerifyAndUnblindInvalidSignedTokens) {
  // Arrange
  const base::DictValue dict = BuildUrlResponseBody().Set(
      "signedTokens", base::ListValue().Append(cbr::test::kInvalidBase64));

  // Act
  const auto result = ParseVerifyAndUnblindTokens(dict, cbr::test::GetTokens(),
                                                  cbr::test::GetBlindedTokens(),
                                                  cbr::test::GetPublicKey());

  // Assert
  EXPECT_FALSE(result.has_value());
}

}  // namespace catsxp_ads
