/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions.h"

#include "base/run_loop.h"
#include "base/test/scoped_feature_list.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/test/ad_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/test/creative_set_conversion_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/test/ad_event_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_builder.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"
#include "url/gurl.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsConversionsTest : public test::CatsxpAdsConversionsTestBase {};

TEST_F(CatsxpAdsConversionsTest,
       DoNotCapConversionsWithinDifferentCreativeSets) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad_1 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/true);
  test::BuildAndSaveCreativeSetConversion(ad_1.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad_1, {mojom::ConfirmationType::kServedImpression,
                              mojom::ConfirmationType::kViewedImpression});

  const AdInfo ad_2 = test::BuildAd(mojom::AdType::kSearchResultAd,
                                    /*use_random_uuids=*/true);
  test::BuildAndSaveCreativeSetConversion(ad_2.creative_set_id,
                                          test::kAnotherMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad_2, {mojom::ConfirmationType::kServedImpression,
                              mojom::ConfirmationType::kViewedImpression,
                              mojom::ConfirmationType::kClicked});

  // Act & Assert
  base::RunLoop view_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad_1, ConversionActionType::kViewThrough,
                                  view_through_run_loop.QuitClosure());
  base::RunLoop click_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad_2, ConversionActionType::kClickThrough,
                                  click_through_run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  view_through_run_loop.Run();
  click_through_run_loop.Run();
}

TEST_F(CatsxpAdsConversionsTest, ConvertAdForMatchingCreativeSetConversion) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
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

TEST_F(CatsxpAdsConversionsTest, DoNotCapConversionsWithinTheSameCreativeSet) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kConversionsFeature, {{"creative_set_conversion_cap", "0"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  base::RunLoop view_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  view_through_run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  view_through_run_loop.Run();

  // Act & Assert
  base::RunLoop click_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  click_through_run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  click_through_run_loop.Run();
}

TEST_F(CatsxpAdsConversionsTest, CapConversionsWithinTheSameCreativeSet) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kConversionsFeature, {{"creative_set_conversion_cap", "2"}});

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/true);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  base::RunLoop view_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  view_through_run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  view_through_run_loop.Run();

  base::RunLoop click_through_run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  click_through_run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  click_through_run_loop.Run();

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest, ConvertViewedAdAfterTheSameAdWasDismissed) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kDismissed});

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();
}

TEST_F(CatsxpAdsConversionsTest, DoNotConvertNonViewedOrClickedAds) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(
      ad, {mojom::ConfirmationType::kDismissed,
           mojom::ConfirmationType::kServedImpression,
           mojom::ConfirmationType::kLanded,
           mojom::ConfirmationType::kMarkAdAsInappropriate,
           mojom::ConfirmationType::kSavedAd, mojom::ConfirmationType::kLikedAd,
           mojom::ConfirmationType::kDislikedAd,
           mojom::ConfirmationType::kConversion});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest,
       DoNotConvertAdIfThereIsNoCreativeSetConversion) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest,
       DoNotConvertAdIfThereIsNoMatchingCreativeSetConversion) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMismatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest,
       DoNotConvertAdIfAnotherAdHasConvertedWithinTheSameCreativeSet) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad_1 = test::BuildAd(mojom::AdType::kNotificationAd,
                                    /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad_1.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad_1, {mojom::ConfirmationType::kServedImpression,
                              mojom::ConfirmationType::kViewedImpression,
                              mojom::ConfirmationType::kDismissed});

  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad_1, ConversionActionType::kViewThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();

  AdInfo ad_2 = ad_1;
  ad_2.creative_instance_id = test::kAnotherCreativeInstanceId;
  test::RecordAdEvents(ad_2, {mojom::ConfirmationType::kServedImpression,
                              mojom::ConfirmationType::kViewedImpression,
                              mojom::ConfirmationType::kClicked});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest, DoNotConvertAdIfUrlPatternDoesNotMatch) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMismatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kDismissed});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

TEST_F(CatsxpAdsConversionsTest,
       ConvertAdIfCreativeSetConversionIsOnTheCuspOfExpiring) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvent(ad, mojom::ConfirmationType::kViewedImpression);

  AdvanceClockBy(base::Days(3) - base::Milliseconds(1));

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
  run_loop.Run();
}

TEST_F(CatsxpAdsConversionsTest,
       DoNotConvertAdIfTheCreativeSetConversionHasExpired) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kConversionsFeature);

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*use_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvent(ad, mojom::ConfirmationType::kViewedImpression);

  AdvanceClockBy(base::Days(3));

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain());
}

}  // namespace catsxp_ads
