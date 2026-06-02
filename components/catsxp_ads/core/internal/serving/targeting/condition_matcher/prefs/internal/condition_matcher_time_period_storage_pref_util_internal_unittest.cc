/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_time_period_storage_pref_util_internal.h"

#include "base/time/time.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConditionMatcherTimePeriodStorageUtilTest
    : public test::TestBase {};

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForDefaultDuration) {
  // Act & Assert
  EXPECT_EQ(base::Time(),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForEmptyDuration) {
  // Act & Assert
  EXPECT_EQ(base::Time(),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage="));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForAllDuration) {
  // Act & Assert
  EXPECT_EQ(base::Time(),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage=all"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForDaysDuration) {
  // Act & Assert
  EXPECT_EQ(test::Now() - base::Days(7),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForHoursDuration) {
  // Act & Assert
  EXPECT_EQ(test::Now() - base::Hours(1),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage=1h"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForMinutesDuration) {
  // Act & Assert
  EXPECT_EQ(test::Now() - base::Minutes(30),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage=30m"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       ResolveCutoffForSecondsDuration) {
  // Act & Assert
  EXPECT_EQ(test::Now() - base::Seconds(60),
            MaybeResolveTimePeriodStorageCutoff("time_period_storage=60s"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       DoNotResolveCutoffForInvalidDuration) {
  // Act & Assert
  EXPECT_FALSE(
      MaybeResolveTimePeriodStorageCutoff("time_period_storage=invalid"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       DoNotResolveCutoffForNonTimePeriodStoragePattern) {
  // Act & Assert
  EXPECT_FALSE(MaybeResolveTimePeriodStorageCutoff("not_time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesForEmptyList) {
  // Act & Assert
  EXPECT_DOUBLE_EQ(
      0.0, SumTimePeriodStorageListValues(base::ListValue(),
                                          /*cutoff=*/test::DistantPast()));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesWithAllEntriesWithinDuration) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 5.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(8.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::DistantPast()));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesWithEntriesWithinDuration) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 42.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(3.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::Now() - base::Days(7)));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesWithNoEntriesWithinDuration) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 5.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::Now() - base::Days(7)));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesWithEntryOnCusp) {
  // Arrange
  const base::Time cutoff = test::Now() - base::Days(7);
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", cutoff.InSecondsFSinceUnixEpoch())
                      .Set("value", 7.0))
          .Append(base::DictValue()
                      .Set("day", (cutoff - base::Milliseconds(1))
                                      .InSecondsFSinceUnixEpoch())
                      .Set("value", 42.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(7.0,
                   SumTimePeriodStorageListValues(list, /*cutoff=*/cutoff));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesIgnoresNonDictEntries) {
  // Arrange
  const base::ListValue list =
      base::ListValue().Append("foo").Append(42).Append(
          base::DictValue()
              .Set("day", test::Now().InSecondsFSinceUnixEpoch())
              .Set("value", 7.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(7.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::DistantPast()));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesIgnoresEntriesWithoutDayField) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue().Set("value", 42.0))
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 7.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(7.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::DistantPast()));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesIgnoresEntriesWithoutValueField) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue().Set("day",
                                        test::Now().InSecondsFSinceUnixEpoch()))
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 7.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(7.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::DistantPast()));
}

TEST_F(CatsxpAdsConditionMatcherTimePeriodStorageUtilTest,
       SumListValuesForMultipleEntriesWithinDuration) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 1.0))
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 2.0))
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0));

  // Act & Assert
  EXPECT_DOUBLE_EQ(6.0, SumTimePeriodStorageListValues(
                            list, /*cutoff=*/test::DistantPast()));
}

}  // namespace catsxp_ads
