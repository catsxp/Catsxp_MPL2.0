/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/studies_user_data.h"

#include "base/metrics/field_trial.h"
#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsStudiesUserDataTest : public test::TestBase {};

TEST_F(CatsxpAdsStudiesUserDataTest, BuildStudiesUserDataIfNoFieldTrials) {
  // Arrange
  ASSERT_EQ(0U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": []
                    })JSON"),
            BuildStudiesUserData());
}

TEST_F(CatsxpAdsStudiesUserDataTest, BuildStudiesUserDataForSingleFieldTrial) {
  // Arrange
  const scoped_refptr<base::FieldTrial> field_trial =
      base::FieldTrialList::CreateFieldTrial("CatsxpAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial->group_name());
  ASSERT_EQ(1U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": [
                        {
                          "group": "GroupA",
                          "name": "CatsxpAds.FooStudy"
                        }
                      ]
                    }
                )JSON"),
            BuildStudiesUserData());
}

TEST_F(CatsxpAdsStudiesUserDataTest,
       DoNotBuildStudiesUserDataForMultipleFieldTrials) {
  // Arrange
  const scoped_refptr<base::FieldTrial> field_trial_1 =
      base::FieldTrialList::CreateFieldTrial("CatsxpAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial_1->group_name());

  const scoped_refptr<base::FieldTrial> field_trial_2 =
      base::FieldTrialList::CreateFieldTrial("CatsxpAds.BarStudy", "GroupB");
  ASSERT_EQ("GroupB", field_trial_2->group_name());

  ASSERT_EQ(2U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": []
                    })JSON"),
            BuildStudiesUserData());
}

TEST_F(CatsxpAdsStudiesUserDataTest,
       DoNotBuildStudiesUserDataForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const scoped_refptr<base::FieldTrial> field_trial =
      base::FieldTrialList::CreateFieldTrial("CatsxpAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial->group_name());
  ASSERT_EQ(1U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_THAT(BuildStudiesUserData(), ::testing::IsEmpty());
}

}  // namespace catsxp_ads
