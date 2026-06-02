/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration_confirmations_json_parser.h"

#include "base/test/task_environment.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_constants.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads::json::reader {

class CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest
    : public ::testing::Test {
 protected:
  base::test::TaskEnvironment task_environment_;
};

namespace {

// Minimal non-reward confirmation JSON fragment for use in tests.
constexpr char kConfirmationJson[] = R"JSON({
  "confirmations": {
    "queue": [
      {
        "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
        "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
        "type": "view",
        "ad_type": "ad_notification",
        "created_at": 23317004800000000.0,
        "user_data": {}
      }
    ]
  }
})JSON";

}  // namespace

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmations) {
  // Act
  std::optional<ConfirmationList> confirmations =
      ParseConfirmations(kConfirmationJson);

  // Assert
  EXPECT_THAT(confirmations,
              ::testing::Optional(::testing::ElementsAre(::testing::FieldsAre(
                  /*transaction_id*/ "8b742869-6e4a-490c-ac31-31b49130098a",
                  /*creative_instance_id*/
                  "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
                  mojom::ConfirmationType::kViewedImpression,
                  mojom::AdType::kNotificationAd,
                  /*created_at=*/::testing::_,
                  /*reward*/ std::nullopt,
                  /*user_data=*/::testing::_))));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsLegacyInlineContentAdType) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "ad_type": "inline_content_ad",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsLegacyPromotedContentAdType) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "ad_type": "promoted_content_ad",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingTransactionId) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "ad_type": "ad_notification",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingCreativeInstanceId) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "type": "view",
          "ad_type": "ad_notification",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingType) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "ad_type": "ad_notification",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingAdType) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "created_at": 23317004800000000.0,
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingCreatedAt) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "ad_type": "ad_notification",
          "user_data": {}
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseConfirmationsSkipsMissingUserData) {
  // Act
  std::optional<ConfirmationList> confirmations = ParseConfirmations(R"JSON({
    "confirmations": {
      "queue": [
        {
          "transaction_id": "8b742869-6e4a-490c-ac31-31b49130098a",
          "creative_instance_id": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "type": "view",
          "ad_type": "ad_notification",
          "created_at": 23317004800000000.0
        }
      ]
    }
  })JSON");

  // Assert
  EXPECT_THAT(confirmations, ::testing::Optional(::testing::IsEmpty()));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       DoNotParseConfirmationsIfMissingConfirmationsKey) {
  // Act & Assert
  EXPECT_FALSE(ParseConfirmations(R"JSON({"other_key": {}})JSON"));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       DoNotParseConfirmationsIfMissingQueueKey) {
  // Act & Assert
  EXPECT_FALSE(ParseConfirmations(R"JSON({"confirmations": {}})JSON"));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       DoNotParseConfirmationsIfMalformedJson) {
  // Act & Assert
  EXPECT_FALSE(ParseConfirmations(test::kMalformedJson));
}

TEST_F(CatsxpAdsLegacyConfirmationMigrationConfirmationsJsonParserTest,
       ParseEmptyConfirmationQueue) {
  // Act & Assert
  EXPECT_THAT(ParseConfirmations(R"JSON({"confirmations": {"queue": []}})JSON"),
              ::testing::Optional(::testing::IsEmpty()));
}

}  // namespace catsxp_ads::json::reader
