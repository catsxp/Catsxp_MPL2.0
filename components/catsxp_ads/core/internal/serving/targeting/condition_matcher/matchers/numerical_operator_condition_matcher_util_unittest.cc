/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/matchers/numerical_operator_condition_matcher_util.h"

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsNumericalOperatorConditionMatcherUtilTest
    : public test::TestBase {};

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       GetNumericalOperatorType) {
  // Act & Assert
  EXPECT_EQ(ConditionMatcherOperatorType::kEqual,
            MaybeParseNumericalOperatorType("[R=]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kNotEqual,
            MaybeParseNumericalOperatorType("[R≠]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kGreaterThan,
            MaybeParseNumericalOperatorType("[R>]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kGreaterThanOrEqual,
            MaybeParseNumericalOperatorType("[R≥]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kLessThan,
            MaybeParseNumericalOperatorType("[R<]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kLessThanOrEqual,
            MaybeParseNumericalOperatorType("[R≤]:1"));
  EXPECT_EQ(ConditionMatcherOperatorType::kGreaterThan,
            MaybeParseNumericalOperatorType("[R>]:some.pref.path"));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotGetNumericalOperatorTypeForNonOperator) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseNumericalOperatorType("[T=]:1"));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotGetNumericalOperatorTypeForEmptyCondition) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseNumericalOperatorType(""));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       ResolveNumericalOperandForLiteralInteger) {
  // Act
  const auto numerical_operand =
      MaybeResolveNumericalOperand("[R=]:42", /*virtual_prefs=*/{});
  ASSERT_TRUE(numerical_operand);

  // Assert
  EXPECT_DOUBLE_EQ(42.0, *numerical_operand);
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       ResolveNumericalOperandForLiteralFloat) {
  // Act
  const auto numerical_operand =
      MaybeResolveNumericalOperand("[R=]:3.14", /*virtual_prefs=*/{});
  ASSERT_TRUE(numerical_operand);

  // Assert
  EXPECT_DOUBLE_EQ(3.14, *numerical_operand);
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       ResolveNumericalOperandForPrefPath) {
  // Act
  const auto numerical_operand = MaybeResolveNumericalOperand(
      "[R>]:[virtual]:foo",
      /*virtual_prefs=*/base::DictValue().Set("[virtual]:foo", 7.0));
  ASSERT_TRUE(numerical_operand);

  // Assert
  EXPECT_DOUBLE_EQ(7.0, *numerical_operand);
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForEmptyCondition) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveNumericalOperand("", /*virtual_prefs=*/{}));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForMissingColonInCondition) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveNumericalOperand("[R=]", /*virtual_prefs=*/{}));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForEmptyOperandInCondition) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveNumericalOperand("[R=]:", /*virtual_prefs=*/{}));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForMalformedInput) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveNumericalOperand("[R=]: 1 ", /*virtual_prefs=*/{}));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForUnknownPrefPath) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveNumericalOperand("[R=]:[virtual]:missing",
                                            /*virtual_prefs=*/{}));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotResolveNumericalOperandForNonNumericPrefPath) {
  // Act & Assert
  EXPECT_FALSE(
      MaybeResolveNumericalOperand("[R=]:[virtual]:foo",
                                   /*virtual_prefs=*/base::DictValue().Set(
                                       "[virtual]:foo", "not_a_number")));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorForEmptyValue) {
  // Act & Assert
  EXPECT_FALSE(
      MatchNumericalOperator("", ConditionMatcherOperatorType::kEqual, 0));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest, MatchEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(
      MatchNumericalOperator("1.0", ConditionMatcherOperatorType::kEqual, 1));
  EXPECT_TRUE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kEqual, 1));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(
      MatchNumericalOperator("1.0", ConditionMatcherOperatorType::kEqual, 2));
  EXPECT_FALSE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kEqual, 2));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       MatchNotEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kNotEqual, 2));
  EXPECT_TRUE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kNotEqual, 2));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchNotEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kNotEqual, 1));
  EXPECT_FALSE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kNotEqual, 1));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       MatchGreaterThanOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kGreaterThan, 0));
  EXPECT_TRUE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kGreaterThan, 0));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kGreaterThan, 1));
  EXPECT_FALSE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kGreaterThan, 1));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       MatchGreaterThanOrEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kGreaterThanOrEqual, 0));
  EXPECT_TRUE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kGreaterThanOrEqual, 0));

  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kGreaterThanOrEqual, 1));
  EXPECT_TRUE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kGreaterThanOrEqual, 1));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchGreaterThanOrEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kGreaterThanOrEqual, 2));
  EXPECT_FALSE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kGreaterThanOrEqual, 2));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       MatchLessThanOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kLessThan, 2));
  EXPECT_TRUE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kLessThan, 2));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kLessThan, 1));
  EXPECT_FALSE(
      MatchNumericalOperator("1", ConditionMatcherOperatorType::kLessThan, 1));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       MatchLessThanOrEqualOperator) {
  // Act & Assert
  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kLessThanOrEqual, 1));
  EXPECT_TRUE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kLessThanOrEqual, 1));

  EXPECT_TRUE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kLessThanOrEqual, 2));
  EXPECT_TRUE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kLessThanOrEqual, 2));
}

TEST_F(CatsxpAdsNumericalOperatorConditionMatcherUtilTest,
       DoNotMatchLessThanOrEqualOperator) {
  // Act & Assert
  EXPECT_FALSE(MatchNumericalOperator(
      "1.0", ConditionMatcherOperatorType::kLessThanOrEqual, 0));
  EXPECT_FALSE(MatchNumericalOperator(
      "1", ConditionMatcherOperatorType::kLessThanOrEqual, 0));
}

}  // namespace catsxp_ads
