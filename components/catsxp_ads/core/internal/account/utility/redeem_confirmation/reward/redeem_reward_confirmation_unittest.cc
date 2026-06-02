/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation.h"

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/reward_confirmation_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/reward/test/reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/test/issuers_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/confirmation_tokens/test/confirmation_tokens_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/test/token_generator_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/test/redeem_reward_confirmation_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/test/redeem_confirmation_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/mock_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "net/http/http_status_code.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsRedeemRewardConfirmationTest : public test::TestBase {
 protected:
  RedeemConfirmationDelegateMock delegate_mock_;
  base::WeakPtrFactory<RedeemConfirmationDelegateMock>
      confirmation_delegate_weak_factory_{&delegate_mock_};
};

TEST_F(CatsxpAdsRedeemRewardConfirmationTest, Redeem) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation(*confirmation));

  EXPECT_CALL(delegate_mock_, OnFailedToRedeemConfirmation).Times(0);

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest, RetryRedeemingIfNoIssuers) {
  // Arrange
  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/true);
  ASSERT_TRUE(confirmation);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  EXPECT_FALSE(HasPendingTasks());
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingForFetchPaymentTokenHttpNotFoundResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_NOT_FOUND,
         std::string(net::GetHttpReasonPhrase(net::HTTP_NOT_FOUND))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingForFetchPaymentTokenHttpBadRequestResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_BAD_REQUEST,
         std::string(net::GetHttpReasonPhrase(net::HTTP_BAD_REQUEST))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       RetryRedeemingForFetchPaymentTokenHttpAcceptedResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_ACCEPTED, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       RetryRedeemingForFetchPaymentTokenHttpInternalServerErrorResponse) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_INTERNAL_SERVER_ERROR,
         std::string(
             net::GetHttpReasonPhrase(net::HTTP_INTERNAL_SERVER_ERROR))}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfInvalidResponseBody) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/test::kMalformedJson}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyIdIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyIdDoesNotMatchConfirmationId) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "393abadc-e9ae-4aac-a321-3307e0d527c6",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPaymentTokenIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6"
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPublicKeyIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyPublicKeyIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "INVALID",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       RetryRedeemingIfPublicKeyDoesNotExist) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "paymentToken" : {
                "publicKey" : "Si61i/8huYsx01ED6SZIOvDuD6GQV5LAi2CMu3NAVCQ=",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/true));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyBatchProofIsMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodyBatchProofIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "INVALID",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodySignedTokensAreMissing) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg=="
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfResponseBodySignedTokenIsInvalid) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "6bAH3z5sAoLdtM5tDrSJkhcYi4lp3GY+jh/ubSxTnQCgfkmKve/7s1bcIzvjsLvvPDuWABRZyBml6IzeG86ICg==",
                "signedTokens" : [
                  "INVALID"
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest,
       DoNotRetryRedeemingIfFailedToVerifyAndUnblindTokens) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, /*response_body=*/R"(
            {
              "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
              "createdAt" : "2020-04-20T10:27:11.717Z",
              "type" : "view",
              "modifiedAt" : "2020-04-20T10:27:11.736Z",
              "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
              "paymentToken" : {
                "publicKey" : "OqhZpUC8B15u+Gc11rQYRl8O3zOSAUIEC2JuDHI32TM=",
                "batchProof" : "INVALID",
                "signedTokens" : [
                  "Ktsii4pOKOjfmqziUsdlV3lJETaGXG0rksRujn1i1Qs="
                ]
              }
            })"}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  EXPECT_CALL(delegate_mock_, OnDidRedeemConfirmation).Times(0);

  EXPECT_CALL(delegate_mock_,
              OnFailedToRedeemConfirmation(*confirmation,
                                           /*should_retry=*/false));

  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  FastForwardClockToNextPendingTask();
}

TEST_F(CatsxpAdsRedeemRewardConfirmationTest, FetchPaymentTokenAfter) {
  // Arrange
  test::BuildAndSetIssuers();

  test::MockTokenGenerator(/*count=*/1);
  test::RefillConfirmationTokens(/*count=*/1);

  std::optional<ConfirmationInfo> confirmation =
      test::BuildRewardConfirmation(/*use_random_uuids=*/false);
  ASSERT_TRUE(confirmation);

  const test::URLResponseMap url_responses = {
      {BuildCreateRewardConfirmationUrlPath(
           confirmation->transaction_id,
           confirmation->reward->credential_base64url),
       {{net::HTTP_CREATED,
         test::BuildCreateRewardConfirmationUrlResponseBody()}}},
      {BuildFetchPaymentTokenUrlPath(confirmation->transaction_id),
       {{net::HTTP_OK, test::BuildFetchPaymentTokenUrlResponseBody()}}}};
  test::MockUrlResponses(ads_client_mock_, url_responses);

  // Act & Assert
  RedeemRewardConfirmation::CreateAndRedeem(
      confirmation_delegate_weak_factory_.GetWeakPtr(), *confirmation);

  EXPECT_EQ(kFetchPaymentTokenAfter.Get(), NextPendingTaskDelay());
  EXPECT_EQ(1U, GetPendingTaskCount());
}

}  // namespace catsxp_ads
