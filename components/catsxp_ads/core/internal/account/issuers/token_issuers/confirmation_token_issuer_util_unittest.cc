/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/confirmation_token_issuer_util.h"

#include "base/uuid.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConfirmationsIssuerUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsConfirmationsIssuerUtilTest, IsConfirmationTokenIssuerValid) {
  // Arrange
  TokenIssuerInfo token_issuer;
  token_issuer.type = TokenIssuerType::kConfirmations;

  for (size_t i = 0; i < kMaximumTokenIssuerPublicKeys.Get(); ++i) {
    token_issuer.public_keys.insert(
        {/*public_key=*/base::Uuid::GenerateRandomV4().AsLowercaseString(),
         /*associated_value=*/0.1});
  }

  IssuersInfo issuers;
  issuers.token_issuers.push_back(token_issuer);

  // Act & Assert
  EXPECT_TRUE(IsConfirmationTokenIssuerValid(issuers));
}

TEST_F(CatsxpAdsConfirmationsIssuerUtilTest, IsConfirmationTokenIssuerInvalid) {
  // Arrange
  TokenIssuerInfo token_issuer;
  token_issuer.type = TokenIssuerType::kConfirmations;

  for (size_t i = 0; i < kMaximumTokenIssuerPublicKeys.Get() + 1; ++i) {
    token_issuer.public_keys.insert(
        {/*public_key=*/base::Uuid::GenerateRandomV4().AsLowercaseString(),
         /*associated_value=*/0.1});
  }

  IssuersInfo issuers;
  issuers.token_issuers.push_back(token_issuer);

  // Act & Assert
  EXPECT_FALSE(IsConfirmationTokenIssuerValid(issuers));
}

}  // namespace catsxp_ads
