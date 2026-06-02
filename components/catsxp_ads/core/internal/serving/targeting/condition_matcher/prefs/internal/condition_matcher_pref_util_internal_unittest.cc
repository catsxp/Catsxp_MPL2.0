/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_pref_util_internal.h"

#include "base/containers/span.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/local_state_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConditionMatcherPrefUtilInternalTest : public test::TestBase {};

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotConvertNoneValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(MaybeToString(base::Value()));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, BooleanValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("0", MaybeToString(base::Value(false)));
  EXPECT_EQ("1", MaybeToString(base::Value(true)));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, IntegerValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("123", MaybeToString(base::Value(123)));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, DoubleValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("1.23", MaybeToString(base::Value(1.23)));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, StringValueTypeToString) {
  // Act & Assert
  EXPECT_EQ("123", MaybeToString(base::Value("123")));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotConvertDictValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(MaybeToString(base::Value(base::DictValue().Set("foo", "bar"))));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotConvertListValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(MaybeToString(base::Value(base::ListValue().Append("foo"))));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListVirtualPrefValueWithEntriesWithinDuration) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue().Set(
            "bar",
            base::ListValue()
                .Append(base::DictValue()
                            .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                            .Set("value", 3.0))
                .Append(base::DictValue()
                            .Set("day",
                                 test::DistantPast().InSecondsFSinceUnixEpoch())
                            .Set("value", 7.0))));
  });

  // Act & Assert
  EXPECT_EQ(base::Value(3.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "[virtual]:foo|bar|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListVirtualPrefValueWithNoEntriesWithinDuration) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue().Set(
            "bar",
            base::ListValue().Append(
                base::DictValue()
                    .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                    .Set("value", 7.0))));
  });

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "[virtual]:foo|bar|time_period_storage=7d"));
}

TEST_F(
    CatsxpAdsConditionMatcherPrefUtilInternalTest,
    GetTimePeriodStorageListVirtualPrefValueWithEntriesWithinDefaultDuration) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo",
        base::DictValue().Set(
            "bar",
            base::ListValue()
                .Append(base::DictValue()
                            .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                            .Set("value", 3.0))
                .Append(base::DictValue()
                            .Set("day",
                                 test::DistantPast().InSecondsFSinceUnixEpoch())
                            .Set("value", 7.0))));
  });

  // Act & Assert
  EXPECT_EQ(base::Value(10.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "[virtual]:foo|bar|time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListProfilePrefValueWithEntriesWithinDuration) {
  // Arrange
  test::RegisterProfileListPref(
      "list",
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(3.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(
    CatsxpAdsConditionMatcherPrefUtilInternalTest,
    GetTimePeriodStorageListProfilePrefValueWithEntriesWithinDefaultDuration) {
  // Arrange
  test::RegisterProfileListPref(
      "list",
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(10.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListProfilePrefValueWithNoEntriesWithinDuration) {
  // Arrange
  test::RegisterProfileListPref(
      "list",
      base::ListValue().Append(
          base::DictValue()
              .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
              .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListLocalStatePrefValueWithEntriesWithinDuration) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list",
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(3.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetTimePeriodStorageListLocalStatePrefValueWithNoEntriesWithinDuration) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list",
      base::ListValue().Append(
          base::DictValue()
              .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
              .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(
    CatsxpAdsConditionMatcherPrefUtilInternalTest,
    GetTimePeriodStorageListLocalStatePrefValueWithEntriesWithinDefaultDuration) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list",
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 7.0)));

  // Act & Assert
  EXPECT_EQ(base::Value(10.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetEmptyTimePeriodStorageListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref("list", base::ListValue());

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetEmptyTimePeriodStorageListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref("list", base::ListValue());

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "list|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotConvertEmptyListValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(MaybeToString(base::Value(base::ListValue())));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetEmptyTimePeriodStorageListVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set(
        "[virtual]:foo", base::DictValue().Set("bar", base::ListValue()));
  });

  // Act & Assert
  EXPECT_EQ(base::Value(0.0),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "[virtual]:foo|bar|time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotConvertBinaryValueTypeToString) {
  // Act & Assert
  EXPECT_FALSE(MaybeToString(base::Value(
      base::span<const uint8_t>({0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57,
                                 0x6F, 0x72, 0x6C, 0x64, 0x21}))));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:foo", 1);
  });

  // Act & Assert
  EXPECT_EQ(base::Value(1), MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                                              "[virtual]:foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetUnknownVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:bar", 1);
  });

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "[virtual]:foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetBooleanProfilePrefValue) {
  // Arrange
  test::RegisterProfileBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ(base::Value(true),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "boolean"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetIntegerProfilePrefValue) {
  // Arrange
  test::RegisterProfileIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDoubleProfilePrefValue) {
  // Arrange
  test::RegisterProfileDoublePref("double", 1.23);

  // Act & Assert
  EXPECT_EQ(base::Value(1.23),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "double"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetStringProfilePrefValue) {
  // Arrange
  test::RegisterProfileStringPref("string", "foo");

  // Act & Assert
  EXPECT_EQ(base::Value("foo"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "string"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref("dict", base::DictValue().Set("foo", "bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict",
      base::DictValue().Set("foo", base::DictValue().Set("bar", "qux")));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|bar"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDeeplyNestedDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict",
      base::DictValue().Set("foo", base::ListValue().Append("bar").Append(
                                       base::DictValue().Set("baz", "qux"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|1|baz"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedDictProfilePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterProfileDictPref(
      "dict", base::DictValue().Set("foo.bar",
                                    base::DictValue().Set("baz.qux", "quux")));

  // Act & Assert
  EXPECT_EQ(base::Value("quux"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "dict|foo.bar|baz.qux"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetMalformedDictProfilePrefValue) {
  // Arrange
  test::RegisterProfileDictPref("dict",
                                base::DictValue().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar|baz"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref("list",
                                base::ListValue().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref(
      "list",
      base::ListValue().Append(base::ListValue().Append("foo").Append("bar")));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDeeplyNestedListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::ListValue().Append(base::DictValue().Set(
                  "foo", base::ListValue().Append("bar").Append("baz"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedListProfilePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterProfileListPref(
      "list", base::ListValue().Append(base::DictValue().Set(
                  "foo.bar",
                  base::ListValue().Append("baz.qux").Append("quux.corge"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("quux.corge"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo.bar|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetListProfilePrefValueWithOutOfBoundsListIndicies) {
  // Arrange
  test::RegisterProfileListPref("list",
                                base::ListValue().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|-1"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|2"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetMalformedListProfilePrefValue) {
  // Arrange
  test::RegisterProfileListPref("list", base::ListValue().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|bar"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetBooleanLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ(base::Value(true),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "boolean"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetIntegerLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDoubleLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDoublePref("double", 1.23);

  // Act & Assert
  EXPECT_EQ(base::Value(1.23),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "double"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetStringLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateStringPref("string", "foo");

  // Act & Assert
  EXPECT_EQ(base::Value("foo"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "string"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref("dict",
                                   base::DictValue().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict",
      base::DictValue().Set("foo", base::DictValue().Set("bar", "qux")));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|bar"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDeeplyNestedDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict",
      base::DictValue().Set("foo", base::ListValue().Append("bar").Append(
                                       base::DictValue().Set("baz", "qux"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("qux"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo|1|baz"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedDictLocalStatePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterLocalStateDictPref(
      "dict", base::DictValue().Set("foo.bar",
                                    base::DictValue().Set("baz.qux", "quux")));

  // Act & Assert
  EXPECT_EQ(base::Value("quux"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(),
                              "dict|foo.bar|baz.qux"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetMalformedDictLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateDictPref("dict",
                                   base::DictValue().Set("foo.bar", "baz"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|foo.bar|baz"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "dict|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::ListValue().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list",
      base::ListValue().Append(base::ListValue().Append("foo").Append("bar")));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"),
            MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetDeeplyNestedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::ListValue().Append(base::DictValue().Set(
                  "foo", base::ListValue().Append("bar").Append("baz"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("baz"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetNestedListLocalStatePrefValueWithDotSeparatedPathComponents) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::ListValue().Append(base::DictValue().Set(
                  "foo.bar",
                  base::ListValue().Append("baz.qux").Append("quux.corge"))));

  // Act & Assert
  EXPECT_EQ(
      base::Value("quux.corge"),
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo.bar|1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetMalformedListLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateListPref("list", base::ListValue().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|0|foo"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|bar"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "|"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), ""));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetListLocalStatePrefValueWithOutOfBoundsListIndicies) {
  // Arrange
  test::RegisterLocalStateListPref(
      "list", base::ListValue().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|-1"));
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "list|2"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetRootVirtualPrefValue) {
  // Arrange
  ON_CALL(ads_client_mock_, GetVirtualPrefs).WillByDefault([]() {
    return base::DictValue().Set("[virtual]:foo", 1);
  });

  // Act & Assert
  EXPECT_EQ(
      base::Value(1),
      MaybeGetRootPrefValue(GetAdsClient().GetVirtualPrefs(), "[virtual]:foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetRootProfilePrefValue) {
  // Arrange
  test::RegisterProfileIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetRootPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetRootLocalStatePrefValue) {
  // Arrange
  test::RegisterLocalStateIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ(base::Value(123),
            MaybeGetRootPrefValue(GetAdsClient().GetVirtualPrefs(), "integer"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetRootUnknownPrefValue) {
  // Act & Assert
  EXPECT_FALSE(
      MaybeGetRootPrefValue(GetAdsClient().GetVirtualPrefs(), "unknown"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetDictPrefValue) {
  // Arrange
  const base::DictValue dict = base::DictValue().Set("foo", "bar");

  // Act & Assert
  EXPECT_EQ(base::Value("bar"), MaybeGetDictPrefValue(dict, "foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetUnknownDictPrefValue) {
  // Arrange
  const base::DictValue dict = base::DictValue().Set("foo", "bar");

  // Act & Assert
  EXPECT_FALSE(MaybeGetDictPrefValue(dict, "baz"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetListPrefValueByIndex) {
  // Arrange
  const base::ListValue list = base::ListValue().Append("foo").Append("bar");

  // Act & Assert
  EXPECT_EQ(base::Value("bar"), MaybeGetListPrefValue(list, "1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetListPrefValueWithOutOfBoundsIndex) {
  // Arrange
  const base::ListValue list = base::ListValue().Append("foo");

  // Act & Assert
  EXPECT_FALSE(MaybeGetListPrefValue(list, "1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetListPrefValueWithNonIntegerKey) {
  // Arrange
  const base::ListValue list = base::ListValue().Append("foo");

  // Act & Assert
  EXPECT_FALSE(MaybeGetListPrefValue(list, "bar"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       GetListPrefValueWithTimePeriodStorageSum) {
  // Arrange
  const base::ListValue list =
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(
              base::DictValue()
                  .Set("day", test::DistantPast().InSecondsFSinceUnixEpoch())
                  .Set("value", 7.0));

  // Act & Assert
  EXPECT_EQ(base::Value(3.0),
            MaybeGetListPrefValue(list, "time_period_storage=7d"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetListPrefValueWithInvalidTimePeriodStorageDuration) {
  // Arrange
  const base::ListValue list = base::ListValue().Append(
      base::DictValue()
          .Set("day", test::Now().InSecondsFSinceUnixEpoch())
          .Set("value", 3.0));

  // Act & Assert
  EXPECT_FALSE(MaybeGetListPrefValue(list, "time_period_storage=invalid"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetNextDictPrefValue) {
  // Arrange
  const base::Value pref_value(base::DictValue().Set("foo", "bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"), MaybeGetNextPrefValue(pref_value, "foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, GetNextListPrefValue) {
  // Arrange
  const base::Value pref_value(base::ListValue().Append("foo").Append("bar"));

  // Act & Assert
  EXPECT_EQ(base::Value("bar"), MaybeGetNextPrefValue(pref_value, "1"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest,
       DoNotGetNextScalarPrefValue) {
  // Arrange
  const base::Value pref_value("scalar");

  // Act & Assert
  EXPECT_FALSE(MaybeGetNextPrefValue(pref_value, "foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilInternalTest, DoNotGetUnknownPrefValue) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValue(GetAdsClient().GetVirtualPrefs(), "foo.bar"));
}

}  // namespace catsxp_ads
