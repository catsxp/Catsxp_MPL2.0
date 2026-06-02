/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/epoch_operator_condition_matcher_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsEpochOperatorConditionMatcherUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest, GetEpochOperatorType) {
  // Act & Assert
  EXPECT_EQ(ConditionMatcherOperatorType::kEqual,
            MaybeParseEpochOperatorType("[T=]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kNotEqual,
            MaybeParseEpochOperatorType("[T≠]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kGreaterThan,
            MaybeParseEpochOperatorType("[T>]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kGreaterThanOrEqual,
            MaybeParseEpochOperatorType("[T≥]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kLessThan,
            MaybeParseEpochOperatorType("[T<]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kLessThanOrEqual,
            MaybeParseEpochOperatorType("[T≤]:1"));
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotGetEpochOperatorTypeForNonOperator) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseEpochOperatorType("[R=]:1"));
  EXPECT_FALSE(MaybeParseEpochOperatorType("[T_]:2"));
  EXPECT_FALSE(MaybeParseEpochOperatorType("baz"));
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchMalformedOperator) {
  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kEqual, "[T=]: 7 "));
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest, MatchEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kEqual, "[T=]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest, DoNotMatchEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kEqual, "[T=]:3"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest, MatchNotEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kNotEqual, "[T≠]:3"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchNotEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kNotEqual, "[T≠]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       MatchGreaterThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kGreaterThan, "[T>]:1"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kGreaterThan, "[T>]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       MatchGreaterThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kGreaterThanOrEqual,
                         "[T≥]:1"));  // 2 days ago.
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kGreaterThanOrEqual,
                         "[T≥]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kGreaterThanOrEqual,
                         "[T≥]:3"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest, MatchLessThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kLessThan, "[T<]:3"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(MatchEpochOperator(
      "13372214400000000" /*1st October 2024 00:00:00 UTC*/,
      ConditionMatcherOperatorType::kLessThan, "[T<]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       MatchLessThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kLessThanOrEqual,
                         "[T≤]:3"));  // 2 days ago.
  EXPECT_TRUE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kLessThanOrEqual,
                         "[T≤]:2"));  // 2 days ago.
}

TEST_F(CatsxpAdsEpochOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOrEqualOperator) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("3 October 2024"));

  // Act & Assert
  EXPECT_FALSE(
      MatchEpochOperator("13372214400000000" /*1st October 2024 00:00:00 UTC*/,
                         ConditionMatcherOperatorType::kLessThanOrEqual,
                         "[T≤]:1"));  // 2 days ago.
}

}  // namespace catsxp_ads
