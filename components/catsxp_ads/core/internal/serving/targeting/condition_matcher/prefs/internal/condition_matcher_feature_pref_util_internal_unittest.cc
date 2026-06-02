/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_feature_pref_util_internal.h"

#include "base/feature_list.h"
#include "base/test/scoped_feature_list.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"

// npm run test -- catsxp_all_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {
BASE_FEATURE(kTestFeature, base::FEATURE_ENABLED_BY_DEFAULT);
}  // namespace

class CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest
    : public test::TestBase {};

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       GetIsOverriddenWhenFeatureIsOverridden) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(kTestFeature);

  // Act
  std::optional<base::Value> feature_dict =
      MaybeGetFeaturePrefValue("[virtual]:feature=TestFeature");

  // Assert
  ASSERT_TRUE(feature_dict);
  EXPECT_EQ("1", *feature_dict->GetDict().FindString("is_overridden"));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       GetIsNotOverriddenWhenFeatureIsNotOverridden) {
  // Act
  std::optional<base::Value> feature_dict =
      MaybeGetFeaturePrefValue("[virtual]:feature=TestFeature");

  // Assert
  ASSERT_TRUE(feature_dict);
  EXPECT_EQ("0", *feature_dict->GetDict().FindString("is_overridden"));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       GetParamsWhenFeatureHasTrial) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(kTestFeature,
                                                         {{"foo", "bar"}});

  // Act
  std::optional<base::Value> feature_dict =
      MaybeGetFeaturePrefValue("[virtual]:feature=TestFeature");

  // Assert
  ASSERT_TRUE(feature_dict);
  const auto* const params_dict = feature_dict->GetDict().FindDict("params");
  ASSERT_TRUE(params_dict);
  EXPECT_EQ("bar", *params_dict->FindString("foo"));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       DoNotGetParamsDictWhenFeatureHasNoTrial) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(kTestFeature);

  // Act
  std::optional<base::Value> feature_dict =
      MaybeGetFeaturePrefValue("[virtual]:feature=TestFeature");

  // Assert
  ASSERT_TRUE(feature_dict);
  EXPECT_FALSE(feature_dict->GetDict().FindDict("params"));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       DoNotGetFeaturePrefValueForNonKeywordPath) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetFeaturePrefValue("TestFeature"));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       DoNotGetFeaturePrefValueForEmptyFeatureName) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetFeaturePrefValue("[virtual]:feature="));
}

TEST_F(CatsxpAdsConditionMatcherFeaturePrefUtilInternalTest,
       DoNotGetFeaturePrefValueForKeywordWithNoEqualsSign) {
  // Act & Assert
  EXPECT_FALSE(MaybeGetFeaturePrefValue("[virtual]:feature"));
}

}  // namespace catsxp_ads
