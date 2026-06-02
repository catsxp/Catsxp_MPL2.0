/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_credential_json_writer.h"

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/test/reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRewardCredentialJsonWriterTest : public test::TestBase {};

TEST_F(CatsxpAdsRewardCredentialJsonWriterTest, WriteRewardCredential) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const RewardInfo reward = test::BuildReward(*confirmation);

  // Act
  std::optional<std::string> reward_credential =
      json::writer::WriteRewardCredential(
          reward,
          /*payload=*/"definition: the weight of a payload");
  ASSERT_TRUE(reward_credential);

  // Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "signature": "jo8LVg8FpHtLKMakT7WcfGulrCB6ttSJpAaMcD95pDKTcdBRVf1yUDEZmhLKXWTIPDCDRCPKEx3gChO4S5GtHw==",
                      "t": "/mfTAAjHrWmAlLiEktbqNS/dxoMVdnz1esoVplQUs7yG/apAq2K6OeST6lBTKFJmOq7rV8QbY/DF2HFRMcz/JQ=="
                    })JSON"),
            base::test::ParseJsonDict(*reward_credential));
}

}  // namespace catsxp_ads
