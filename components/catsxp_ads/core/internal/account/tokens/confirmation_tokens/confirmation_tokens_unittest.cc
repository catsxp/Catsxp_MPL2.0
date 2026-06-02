/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_tokens.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/confirmation_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationTokensTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationTokensTest, GetToken) {
  // Arrange
  const ConfirmationTokenList tokens =
      test::BuildConfirmationTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set(tokens);

  // Act & Assert
  EXPECT_EQ(tokens.front(), confirmation_tokens.Get());
}

TEST_F(CatsxpAdsConfirmationTokensTest, GetAllTokens) {
  // Arrange
  const ConfirmationTokenList tokens =
      test::BuildConfirmationTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set(tokens);

  // Act & Assert
  EXPECT_EQ(tokens, confirmation_tokens.GetAll());
}

TEST_F(CatsxpAdsConfirmationTokensTest, SetTokens) {
  // Arrange
  const ConfirmationTokenList tokens =
      test::BuildConfirmationTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  ConfirmationTokens confirmation_tokens;

  // Act
  confirmation_tokens.Set(tokens);

  // Assert
  EXPECT_EQ(tokens, confirmation_tokens.GetAll());
}

TEST_F(CatsxpAdsConfirmationTokensTest, SetEmptyTokens) {
  // Arrange
  ConfirmationTokens confirmation_tokens;

  // Act
  confirmation_tokens.Set({});

  // Assert
  EXPECT_TRUE(confirmation_tokens.IsEmpty());
}

TEST_F(CatsxpAdsConfirmationTokensTest, AddTokens) {
  // Arrange
  const ConfirmationTokenList tokens =
      test::BuildConfirmationTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set({tokens.at(0)});

  // Act
  confirmation_tokens.Add({tokens.at(1)});

  // Assert
  EXPECT_EQ(2U, confirmation_tokens.Count());
}

TEST_F(CatsxpAdsConfirmationTokensTest, AddEmptyTokens) {
  // Arrange
  ConfirmationTokens confirmation_tokens;

  // Act
  confirmation_tokens.Add({});

  // Assert
  EXPECT_TRUE(confirmation_tokens.IsEmpty());
}

TEST_F(CatsxpAdsConfirmationTokensTest, DoNotAddDuplicateTokens) {
  // Arrange
  const ConfirmationTokenInfo confirmation_token =
      test::BuildConfirmationToken();

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Add({confirmation_token});

  // Act
  confirmation_tokens.Add({confirmation_token});

  // Assert
  EXPECT_EQ(1U, confirmation_tokens.Count());
}

TEST_F(CatsxpAdsConfirmationTokensTest, RemoveToken) {
  // Arrange
  const ConfirmationTokenList tokens =
      test::BuildConfirmationTokens(/*count=*/2);
  ASSERT_THAT(tokens, ::testing::SizeIs(2));

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set(tokens);

  const ConfirmationTokenInfo& token_1 = tokens.at(0);
  const ConfirmationTokenInfo& token_2 = tokens.at(1);

  // Act
  confirmation_tokens.Remove(token_2);

  // Assert
  EXPECT_EQ(ConfirmationTokenList{token_1}, confirmation_tokens.GetAll());
}

TEST_F(CatsxpAdsConfirmationTokensTest, TokenDoesExist) {
  // Arrange
  const ConfirmationTokenInfo confirmation_token =
      test::BuildConfirmationToken();

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set({confirmation_token});

  // Act & Assert
  EXPECT_TRUE(confirmation_tokens.Exists(confirmation_token));
}

TEST_F(CatsxpAdsConfirmationTokensTest, TokenDoesNotExist) {
  // Arrange
  ConfirmationTokens confirmation_tokens;

  // Act & Assert
  EXPECT_FALSE(confirmation_tokens.Exists(test::BuildConfirmationToken()));
}

TEST_F(CatsxpAdsConfirmationTokensTest, Count) {
  // Arrange
  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set(test::BuildConfirmationTokens(/*count=*/3));

  // Act & Assert
  EXPECT_EQ(3U, confirmation_tokens.Count());
}

TEST_F(CatsxpAdsConfirmationTokensTest, IsEmpty) {
  // Arrange
  const ConfirmationTokens confirmation_tokens;

  // Act & Assert
  EXPECT_TRUE(confirmation_tokens.IsEmpty());
}

TEST_F(CatsxpAdsConfirmationTokensTest, IsNotEmpty) {
  // Arrange
  const ConfirmationTokenInfo confirmation_token =
      test::BuildConfirmationToken();

  ConfirmationTokens confirmation_tokens;
  confirmation_tokens.Set({confirmation_token});

  // Act & Assert
  EXPECT_FALSE(confirmation_tokens.IsEmpty());
}

}  // namespace catsxp_ads
