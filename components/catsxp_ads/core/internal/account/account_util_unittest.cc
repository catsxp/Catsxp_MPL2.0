/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

#include "catsxp/components/catsxp_ads/core/internal/account/account_util.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_core/ads_core_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

class CatsxpAdsAccountUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsAccountUtilTest, AlwaysAllowDepositsForRewardsUser) {
  // Act & Assert
  for (size_t i = 0; i < static_cast<size_t>(mojom::AdType::kMaxValue); ++i) {
    for (size_t j = 0;
         j < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++j) {
      EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                     static_cast<mojom::AdType>(i),
                                     static_cast<mojom::ConfirmationType>(j)));
    }
  }
}

TEST_F(CatsxpAdsAccountUtilTest, AllowNewTabPageAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    EXPECT_TRUE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                   mojom::AdType::kNewTabPageAd,
                                   static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    CatsxpAdsAccountUtilTest,
    DoNotAllowNewTabPageAdDepositsForNonRewardsUserIfOptedOutOfNewTabPageAds) {
  // Arrange
  test::DisableCatsxpRewards();

  test::OptOutOfNewTabPageAds();

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNewTabPageAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(
    CatsxpAdsAccountUtilTest,
    DoNotAllowNewTabPageAdDepositsForNonRewardsUserWhenMetricTypeIsDisabled) {
  // Arrange
  test::DisableCatsxpRewards();

  UpdateReportMetricState(test::kCreativeInstanceId,
                          mojom::NewTabPageAdMetricType::kDisabled);

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNewTabPageAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(CatsxpAdsAccountUtilTest,
       DoNotAllowNotificationAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    EXPECT_FALSE(IsAllowedToDeposit(test::kCreativeInstanceId,
                                    mojom::AdType::kNotificationAd,
                                    static_cast<mojom::ConfirmationType>(i)));
  }
}

TEST_F(CatsxpAdsAccountUtilTest,
       OnlyAllowSearchResultAdConversionDepositForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  // Act & Assert
  for (size_t i = 0;
       i < static_cast<size_t>(mojom::ConfirmationType::kMaxValue); ++i) {
    const auto confirmation_type = static_cast<mojom::ConfirmationType>(i);

    const bool is_allowed_to_deposit =
        IsAllowedToDeposit(test::kCreativeInstanceId,
                           mojom::AdType::kSearchResultAd, confirmation_type);

    if (confirmation_type == mojom::ConfirmationType::kConversion) {
      EXPECT_TRUE(is_allowed_to_deposit);
    } else {
      EXPECT_FALSE(is_allowed_to_deposit);
    }
  }
}

}  // namespace catsxp_ads
