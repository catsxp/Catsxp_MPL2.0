/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/reward_confirmation_payload_util.h"

#include <optional>

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/test/reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRewardConfirmationPayloadUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsRewardConfirmationPayloadUtilTest,
       BuildRewardConfirmationPayload) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const RewardInfo reward = test::BuildReward(*confirmation);

  // Act &s Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "blindedPaymentTokens": [
                        "+qJiMi6k0hRzRAEN239nLthLqrNm53O78x/PV8I/JS0="
                      ],
                      "publicKey": "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM="
                    })JSON"),
            BuildRewardConfirmationPayload(reward));
}

}  // namespace catsxp_ads
