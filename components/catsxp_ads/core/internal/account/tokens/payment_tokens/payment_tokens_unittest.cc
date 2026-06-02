/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_tokens.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/test/payment_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPaymentTokensTest : public test::TestBase {};

TEST_F(CatsxpAdsPaymentTokensTest, GetAllTokens) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/2));

  // Act & Assert
  EXPECT_EQ(test::BuildPaymentTokens(/*count=*/2),
            payment_tokens.GetAllTokens());
}

TEST_F(CatsxpAdsPaymentTokensTest, SetTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/2));

  // Assert
  EXPECT_EQ(test::BuildPaymentTokens(/*count=*/2),
            payment_tokens.GetAllTokens());
}

TEST_F(CatsxpAdsPaymentTokensTest, SetEmptyTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.SetTokens({});

  // Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(CatsxpAdsPaymentTokensTest, AddTokens) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens({tokens.at(0)});

  // Act
  payment_tokens.AddTokens({tokens.at(1)});

  // Assert
  EXPECT_EQ(2U, payment_tokens.Count());
}

TEST_F(CatsxpAdsPaymentTokensTest, AddEmptyTokens) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act
  payment_tokens.AddTokens({});

  // Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(CatsxpAdsPaymentTokensTest, DoNotAddDuplicateTokens) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  PaymentTokens payment_tokens;
  payment_tokens.AddTokens({payment_token});

  // Act
  payment_tokens.AddTokens({payment_token});

  // Assert
  EXPECT_EQ(1U, payment_tokens.Count());
}

TEST_F(CatsxpAdsPaymentTokensTest, RemoveTokens) {
  // Arrange
  const PaymentTokenList tokens = test::BuildPaymentTokens(/*count=*/3);
  ASSERT_THAT(tokens, ::testing::SizeIs(3));

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(tokens);

  const PaymentTokenInfo& token_1 = tokens.at(0);
  const PaymentTokenInfo& token_2 = tokens.at(1);
  const PaymentTokenInfo& token_3 = tokens.at(2);

  // Act
  payment_tokens.RemoveTokens({token_1, token_3});

  // Assert
  EXPECT_EQ(PaymentTokenList{token_2}, payment_tokens.GetAllTokens());
}

TEST_F(CatsxpAdsPaymentTokensTest, TokenDoesExist) {
  // Arrange
  const PaymentTokenInfo payment_token = test::BuildPaymentToken();

  PaymentTokens payment_tokens;
  payment_tokens.SetTokens({payment_token});

  // Act & Assert
  EXPECT_TRUE(payment_tokens.TokenExists(payment_token));
}

TEST_F(CatsxpAdsPaymentTokensTest, TokenDoesNotExist) {
  // Arrange
  PaymentTokens payment_tokens;

  // Act & Assert
  EXPECT_FALSE(payment_tokens.TokenExists(test::BuildPaymentToken()));
}

TEST_F(CatsxpAdsPaymentTokensTest, Count) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/3));

  // Act & Assert
  EXPECT_EQ(3U, payment_tokens.Count());
}

TEST_F(CatsxpAdsPaymentTokensTest, IsEmpty) {
  // Arrange
  const PaymentTokens payment_tokens;

  // Act & Assert
  EXPECT_TRUE(payment_tokens.IsEmpty());
}

TEST_F(CatsxpAdsPaymentTokensTest, IsNotEmpty) {
  // Arrange
  PaymentTokens payment_tokens;
  payment_tokens.SetTokens(test::BuildPaymentTokens(/*count=*/1));

  // Act & Assert
  EXPECT_FALSE(payment_tokens.IsEmpty());
}

}  // namespace catsxp_ads
