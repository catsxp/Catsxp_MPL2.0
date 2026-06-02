/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/credential_builder.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/test/challenge_bypass_ristretto_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/unblinded_token.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsCredentialBuilderTest, BuildCredential) {
  // Act
  std::optional<base::DictValue> credential = cbr::MaybeBuildCredential(
      cbr::UnblindedToken(cbr::test::kUnblindedTokenBase64),
      /*payload=*/"definition: the weight of a payload");
  ASSERT_TRUE(credential);

  // Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "signature": "PblFP7WI3ZC3aAX73A9UvBdqnvl87Wx8nnz9DIbhNjxbFamMZGbwn5Hi+FXsSXg2GZ671rCwQ6Xpwe61JjeW9Q==",
                      "t": "IXDCnZnVEJ0orkbZfr2ut2NQPQ0ofdervKBmQ2hyjcClGCjA3/ExbBumO0ua5cxwo//nN0uKQ60kknru8hRXxw=="
                    })JSON"),
            *credential);
}

}  // namespace catsxp_ads
