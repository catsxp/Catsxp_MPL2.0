/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/condition_matcher_pref_util.h"

#include "base/containers/span.h"
#include "base/time/time.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/local_state_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/profile_pref_registry_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConditionMatcherPrefUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       GetBooleanProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ("1", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                           "boolean"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       GetIntegerProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileIntegerPref("integer", 123);

  // Act & Assert
  EXPECT_EQ("123", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                             "integer"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       GetDoubleProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileDoublePref("double", 1.23);

  // Act & Assert
  EXPECT_EQ("1.23", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                              "double"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       GetStringProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileStringPref("string", "foo");

  // Act & Assert
  EXPECT_EQ("foo", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                             "string"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       GetBooleanLocalStatePrefValueAsString) {
  // Arrange
  test::RegisterLocalStateBooleanPref("boolean", true);

  // Act & Assert
  EXPECT_EQ("1", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                           "boolean"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest, GetVirtualPrefValueAsString) {
  // Arrange
  const base::DictValue virtual_prefs =
      base::DictValue().Set("[virtual]:foo", 42);

  // Act & Assert
  EXPECT_EQ("42", MaybeGetPrefValueAsString(virtual_prefs, "[virtual]:foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       DoNotGetDictProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileDictPref("dict", base::DictValue().Set("key", "bar"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(), "dict"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       DoNotGetBinaryVirtualPrefValueAsString) {
  // Arrange
  const base::DictValue virtual_prefs = base::DictValue().Set(
      "[virtual]:foo",
      base::Value(base::span<const uint8_t>({0x48, 0x65, 0x6C, 0x6C, 0x6F})));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValueAsString(virtual_prefs, "[virtual]:foo"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       DoNotGetListProfilePrefValueAsString) {
  // Arrange
  test::RegisterProfileListPref("list", base::ListValue().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(), "list"));
}

TEST_F(
    CatsxpAdsConditionMatcherPrefUtilTest,
    GetListProfilePrefValueAsStringWithTimePeriodStorageKeywordPathComponent) {
  // Arrange
  test::RegisterProfileListPref(
      "list",
      base::ListValue()
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 3.0))
          .Append(base::DictValue()
                      .Set("day", test::Now().InSecondsFSinceUnixEpoch())
                      .Set("value", 5.0)));

  // Act & Assert
  EXPECT_EQ("8", MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                           "list|time_period_storage"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest,
       DoNotGetListProfilePrefValueAsStringWithUnknownKeywordPathComponent) {
  // Arrange
  test::RegisterProfileListPref("list", base::ListValue().Append("foo"));

  // Act & Assert
  EXPECT_FALSE(MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(),
                                         "list|invalid"));
}

TEST_F(CatsxpAdsConditionMatcherPrefUtilTest, DoNotGetUnknownPrefValueAsString) {
  // Act & Assert
  EXPECT_FALSE(
      MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(), "foo.bar"));
  EXPECT_FALSE(MaybeGetPrefValueAsString(GetAdsClient().GetVirtualPrefs(), ""));
}

}  // namespace catsxp_ads
