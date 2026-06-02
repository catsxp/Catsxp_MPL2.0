/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/redeem_non_reward_confirmation.h"

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/non_reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/non_reward/test/non_reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/test/redeem_non_reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/non_reward/url_request_builders/create_non_reward_confirmation_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/test/redeem_confirmation_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRedeemNonRewardConfirmationTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::DisableCatsxpRewards();
  }

  RedeemConfirmationDelegateMock delegate_mock_;
  base::WeakPtrFactory<RedeemConfirmationDelegateMock>
      confirmation_delegate_weak_factory_{&delegate_mock_};
};

TEST_F(CatsxpAdsRedeemNonRewardConfirmationTest, Redeem) {
  // Arrange
  std::optional<ConfirmationInfo> confirmation =
      test::BuildNonRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateNonRewardConfirmationUrlPath(confirmation->transaction_id),
       {{net::HTTP_NO_CONTENT,
         test::BuildCreateNonRewardConfirmationUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation(*confirmation));

  EXPECT_CALL(delegate_mock_, OnFailedToRedeemConfirmation).Times(0);

  RedeemNonRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);
}

TEST_F(CatsxpAdsRedeemNonRewardConfirmationTest, RetryRedeeming) {
  // Arrange
  std::optional<ConfirmationInfo> confirmation =
      test::BuildNonRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateNonRewardConfirmationUrlPath(confirmation->transaction_id),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         /*response_body=*/std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_, OnFailedToRedeemConfirmation(
                                  *confirmation, /*should_retry=*/true));

  RedeemNonRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);
}

}  // namespace catsxp_ads
