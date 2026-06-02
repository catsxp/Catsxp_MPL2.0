/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_value_util.h"

#include <string_view>

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kReactionMapAsJson =
    R"JSON(
        {
          "5484a63f-eb99-4ba5-a3b0-8c25d3c0e4b2": 1,
          "untargeted": 2
        })JSON";

constexpr std::string_view kReactionSetAsJson =
    R"JSON(
        [
          "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
          "c2ba3e7d-f688-4bc4-a053-cbe7ac1e6123"
        ])JSON";

}  // namespace

TEST(CatsxpAdsReactionsValueUtilTest, ReactionMapToDict) {
  // Arrange
  const ReactionMap reactions = {
      {test::kAdvertiserId, mojom::ReactionType::kLiked},
      {test::kSegment, mojom::ReactionType::kDisliked}};

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(kReactionMapAsJson),
            ReactionMapToDict(reactions));
}

TEST(CatsxpAdsReactionsValueUtilTest, EmptyReactionMapToDict) {
  // Act & Assert
  EXPECT_THAT(ReactionMapToDict({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsReactionsValueUtilTest, ReactionMapFromDict) {
  // Arrange
  const base::DictValue dict = base::test::ParseJsonDict(kReactionMapAsJson);

  // Act & Assert
  const ReactionMap expected_reactions = {
      {test::kAdvertiserId, mojom::ReactionType::kLiked},
      {test::kSegment, mojom::ReactionType::kDisliked}};
  EXPECT_EQ(expected_reactions, ReactionMapFromDict(dict));
}

TEST(CatsxpAdsReactionsValueUtilTest, ReactionMapFromEmptyDict) {
  // Act & Assert
  EXPECT_THAT(ReactionMapFromDict({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsReactionsValueUtilTest, ReactionSetToList) {
  // Arrange
  const ReactionSet reactions = {test::kCreativeInstanceId,
                                 test::kCreativeSetId};

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonList(kReactionSetAsJson),
            ReactionSetToList(reactions));
}

TEST(CatsxpAdsReactionsValueUtilTest, EmptyReactionSetToList) {
  // Act & Assert
  EXPECT_THAT(ReactionSetToList({}), ::testing::IsEmpty());
}

TEST(CatsxpAdsReactionsValueUtilTest, ReactionSetFromList) {
  // Arrange
  const base::ListValue list = base::test::ParseJsonList(kReactionSetAsJson);

  // Act & Assert
  const ReactionSet expected_reactions = {test::kCreativeInstanceId,
                                          test::kCreativeSetId};
  EXPECT_EQ(expected_reactions, ReactionSetFromList(list));
}

TEST(CatsxpAdsReactionsValueUtilTest, ReactionSetFromEmptyList) {
  // Act & Assert
  EXPECT_THAT(ReactionSetFromList({}), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
