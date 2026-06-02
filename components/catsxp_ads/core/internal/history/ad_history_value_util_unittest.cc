/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/ad_history_value_util.h"

#include <string_view>

#include "base/test/values_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/history/test/ad_history_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

namespace {

constexpr std::string_view kAdHistoryAsJson = R"JSON(
  [
    {
      "adDetailRows": [
        {
          "adContent": {
            "adAction": "view",
            "adType": "ad_notification",
            "advertiserId": "5484a63f-eb99-4ba5-a3b0-8c25d3c0e4b2",
            "brand": "Test Ad Title",
            "brandDisplayUrl": "catsxp.com",
            "brandInfo": "Test Ad Description",
            "brandUrl": "https://catsxp.com/",
            "campaignId": "84197fc8-830a-4a8e-8339-7a70c2bfa104",
            "creativeInstanceId": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
            "creativeSetId": "c2ba3e7d-f688-4bc4-a053-cbe7ac1e6123",
            "flaggedAd": false,
            "likeAction": 0,
            "placementId": "9bac9ae4-693c-4569-9b3e-300e357780cf",
            "savedAd": false,
            "segment": "untargeted"
          },
          "categoryContent": {
            "category": "untargeted",
            "optAction": 0
          },
          "createdAt": "12993327900000000"
        }
      ],
      "timestampInMilliseconds": 1348854300000,
      "uuid": "0"
    },
    {
      "adDetailRows": [
        {
          "adContent": {
            "adAction": "click",
            "adType": "ad_notification",
            "advertiserId": "5484a63f-eb99-4ba5-a3b0-8c25d3c0e4b2",
            "brand": "Test Ad Title",
            "brandDisplayUrl": "catsxp.com",
            "brandInfo": "Test Ad Description",
            "brandUrl": "https://catsxp.com/",
            "campaignId": "84197fc8-830a-4a8e-8339-7a70c2bfa104",
            "creativeInstanceId": "546fe7b0-5047-4f28-a11c-81f14edcf0f6",
            "creativeSetId": "c2ba3e7d-f688-4bc4-a053-cbe7ac1e6123",
            "flaggedAd": false,
            "likeAction": 0,
            "placementId": "9bac9ae4-693c-4569-9b3e-300e357780cf",
            "savedAd": false,
            "segment": "untargeted"
          },
          "categoryContent": {
            "category": "untargeted",
            "optAction": 0
          },
          "createdAt": "12993327900000000"
        }
      ],
      "timestampInMilliseconds": 1348854300000,
      "uuid": "1"
    }
  ])JSON";

}  // namespace

class CatsxpAdsAdHistoryValueUtilTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    AdvanceClockTo(
        test::TimeFromUTCString("Fri, 28 Sep 2012 17:45"));  // Hello Jaxson!!!
  }
};

TEST_F(CatsxpAdsAdHistoryValueUtilTest, AdHistoryToList) {
  // Arrange
  const AdHistoryList ad_history =
      test::BuildAdHistory(mojom::AdType::kNotificationAd,
                           {mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked},
                           /*use_random_uuids=*/false);

  // Act
  const base::ListValue list = AdHistoryToList(ad_history);

  // Assert
  EXPECT_EQ(base::test::ParseJsonList(kAdHistoryAsJson), list);
}

}  // namespace catsxp_ads
