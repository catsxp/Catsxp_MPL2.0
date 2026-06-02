/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/condition_matcher_util.h"

#include "base/time/time.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

void VerifyDoesMatchConditionsExpectation(
    const ConditionMatcherMap& condition_matchers) {
  EXPECT_TRUE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

void VerifyDoesNotMatchConditionsExpectation(
    const ConditionMatcherMap& condition_matchers) {
  EXPECT_FALSE(
      MatchConditions(GetAdsClient().GetVirtualPrefs(), condition_matchers));
}

}  // namespace

class CatsxpAdsConditionMatcherUtilTest : public test::TestBase {
 public:
  CatsxpAdsConditionMatcherUtilTest() {
    // Set the clock to 00:00:00 UTC to ensure that `base::Time::Now()` returns
    // a deterministic value when registering time prefs in individual tests.
    AdvanceClockTo(test::TimeFromUTCString("14 October 2024 00:00:00"));
  }
};

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchEmptyConditions) {
  // Act & Assert
  VerifyDoesMatchConditionsExpectation(/*condition_matchers=*/{});
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchMultipleConditions) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");
  test::RegisterProfileIntegerPref("bar", 1);

  const ConditionMatcherMap condition_matchers = {{"foo", "baz"}, {"bar", "1"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchConditionsIfAnyConditionIsFalse) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");
  test::RegisterProfileIntegerPref("bar", 1);

  const ConditionMatcherMap condition_matchers = {{"foo", "baz"}, {"bar", "0"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchEpochEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileTimePref("foo", base::Time::Now());
  AdvanceClockBy(base::Days(7));

  const ConditionMatcherMap condition_matchers = {{"foo", "[T=]:7"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchEpochEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[T=]:0"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchEpochEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[T=]:1"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchEpochEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileTimePref("foo", base::Time::Now());
  AdvanceClockBy(base::Days(7) - base::Milliseconds(1));

  const ConditionMatcherMap condition_matchers = {{"foo", "[T=]:7"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[R=]:0"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalEqualOperatorConditionForUnknownPrefPath) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"unknown_pref_path", "[R=]:1"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchNumericalEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R=]:5"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R=]:4"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalNotEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≠]:4"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalNotEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≠]:5"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalGreaterThanOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R>]:4"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalGreaterThanOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R>]:5"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalGreaterThanOrEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≥]:5"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalGreaterThanOrEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≥]:6"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalLessThanOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R<]:6"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalLessThanOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R<]:5"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalLessThanOrEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≤]:5"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalLessThanOrEqualOperatorCondition) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  const ConditionMatcherMap condition_matchers = {{"foo", "[R≤]:4"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchPatternCondition) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");

  const ConditionMatcherMap condition_matchers = {{"foo", "?az"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, DoNotMatchPatternCondition) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");

  const ConditionMatcherMap condition_matchers = {{"foo", "?qux*"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, MatchRegexCondition) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");

  const ConditionMatcherMap condition_matchers = {{"foo", "^ba"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest, DoNotMatchRegexCondition) {
  // Arrange
  test::RegisterProfileStringPref("foo", "baz");

  const ConditionMatcherMap condition_matchers = {{"foo", "^qux"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchConditionsIfPrefPathWasNotFound) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {{"foo.bar", "baz"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchConditionsWithNotOperatorWhenPrefPathNotFound) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {{"[!]:foo.bar", "baz"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchConditionsWithNotOperatorWhenPrefExists) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 0);
  test::SetProfileIntegerPrefValue("foo", 5);

  const ConditionMatcherMap condition_matchers = {{"[!]:foo", "baz"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchConditionsWithNotOperatorWhenPrefExistsWithDefaultValue) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);

  const ConditionMatcherMap condition_matchers = {{"[!]:foo", "baz"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchConditionsIfAllConditionsAreFalse) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 1);
  test::RegisterProfileTimePref("bar", base::Time::Now());
  AdvanceClockBy(base::Days(5));

  const ConditionMatcherMap condition_matchers = {
      {"foo", "0"},  // Value is "1" in the pref.
      {"bar", "[T>]:7"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalOperatorComparingTwoPrefs) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 5);
  test::RegisterProfileIntegerPref("bar", 3);

  const ConditionMatcherMap condition_matchers = {{"foo", "[R>]:bar"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorComparingTwoPrefs) {
  // Arrange
  test::RegisterProfileIntegerPref("foo", 3);
  test::RegisterProfileIntegerPref("bar", 5);

  const ConditionMatcherMap condition_matchers = {{"foo", "[R>]:bar"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalOperatorWithVirtualPrefPathOperand) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:foo", 2.0);
  });

  const ConditionMatcherMap condition_matchers = {
      {"foo", "[R<]:[virtual]:foo"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorWithVirtualPrefPathOperand) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:foo", 1.0);
  });

  const ConditionMatcherMap condition_matchers = {
      {"foo", "[R>]:[virtual]:foo"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorWithMissingPrefPathOperand) {
  // Arrange
  const ConditionMatcherMap condition_matchers = {
      {"foo", "[R=]:[virtual]:bar"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorWithNonNumericVirtualPrefPathOperand) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:foo", "bar");
  });

  const ConditionMatcherMap condition_matchers = {
      {"foo", "[R=]:[virtual]:foo"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalOperatorConditionWithTimePeriodStorage) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue().Set(
            "bar",
            base::ListValue()
                .Append(base::DictValue()
                            .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                            .Set("value", 5.0))
                .Append(base::DictValue()
                            .Set("day",
                                 test::DistantPast().InSecondsFSinceUnixEpoch())
                            .Set("value", 3.0))));
  });

  const ConditionMatcherMap condition_matchers = {
      {"[virtual]:foo|bar|time_period_storage=7d", "[R>]:4"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorConditionWithTimePeriodStorage) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue().Set(
            "bar",
            base::ListValue()
                .Append(base::DictValue()
                            .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                            .Set("value", 5.0))
                .Append(base::DictValue()
                            .Set("day",
                                 test::DistantPast().InSecondsFSinceUnixEpoch())
                            .Set("value", 3.0))));
  });

  const ConditionMatcherMap condition_matchers = {
      {"[virtual]:foo|bar|time_period_storage=7d", "[R>]:6"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       MatchNumericalOperatorConditionWithTimePeriodStorageOperand) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue()
            .Set("bar",
                 base::ListValue()
                     .Append(
                         base::DictValue()
                             .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                             .Set("value", 5.0))
                     .Append(base::DictValue()
                                 .Set("day", test::DistantPast()
                                                 .InSecondsFSinceUnixEpoch())
                                 .Set("value", 3.0)))
            .Set("baz",
                 base::ListValue()
                     .Append(
                         base::DictValue()
                             .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                             .Set("value", 3.0))
                     .Append(base::DictValue()
                                 .Set("day", test::DistantPast()
                                                 .InSecondsFSinceUnixEpoch())
                                 .Set("value", 5.0))));
  });

  const ConditionMatcherMap condition_matchers = {
      {"[virtual]:foo|bar|time_period_storage=7d",
       "[R>]:[virtual]:foo|baz|time_period_storage=7d"}};

  // Act & Assert
  VerifyDoesMatchConditionsExpectation(condition_matchers);
}

TEST_F(CatsxpAdsConditionMatcherUtilTest,
       DoNotMatchNumericalOperatorConditionWithTimePeriodStorageOperand) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue()
            .Set("bar",
                 base::ListValue()
                     .Append(
                         base::DictValue()
                             .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                             .Set("value", 5.0))
                     .Append(base::DictValue()
                                 .Set("day", test::DistantPast()
                                                 .InSecondsFSinceUnixEpoch())
                                 .Set("value", 3.0)))
            .Set("baz",
                 base::ListValue()
                     .Append(
                         base::DictValue()
                             .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                             .Set("value", 3.0))
                     .Append(base::DictValue()
                                 .Set("day", test::DistantPast()
                                                 .InSecondsFSinceUnixEpoch())
                                 .Set("value", 5.0))));
  });

  const ConditionMatcherMap condition_matchers = {
      {"[virtual]:foo|baz|time_period_storage=7d",
       "[R>]:[virtual]:foo|bar|time_period_storage=7d"}};

  // Act & Assert
  VerifyDoesNotMatchConditionsExpectation(condition_matchers);
}

}  // namespace catsxp_ads
