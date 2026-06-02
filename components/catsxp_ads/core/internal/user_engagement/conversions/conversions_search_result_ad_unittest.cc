/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/test/creative_set_conversion_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionsSearchResultAdTest
    : public test::CatsxpAdsConversionsTestBase {};

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       ConvertViewedAdIfOptedInToSearchResultAds) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();
}

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       DoNotConvertViewedAdIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       ConvertClickedAdIfOptedInToSearchResultAds) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kClickThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();
}

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       DoNotConvertClickedAdIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       DoNotConvertViewedAdForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));

  // We do not record ad events for non-Rewards users.
  test::RecordAdEvents(ad, /*mojom_confirmation_types=*/{});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsSearchResultAdTest,
       ConvertClickedAdForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));

  // We only record ad clicked and conversion events for non-Rewards users.
  test::RecordAdEvent(ad, mojom::ConfirmationType::kClicked);

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kClickThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();
}

}  // namespace catsxp_ads
