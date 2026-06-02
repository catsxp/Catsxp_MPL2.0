/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"

#include <memory>
#include <utility>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/test/run_until.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/language_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/resource_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/file_path_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource_constants.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTextClassificationResourceTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<TextClassificationResource>();
  }

  std::unique_ptr<TextClassificationResource> resource_;
};

TEST_F(CatsxpAdsTextClassificationResourceTest, IsResourceNotLoaded) {
  // Act & Assert
  EXPECT_FALSE(resource_->GetManifestVersion());
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest, LoadResource) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);

  // Act & Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest, DoNotLoadMalformedResource) {
  // Arrange
  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      /*from_path=*/test::kMalformedResourceId,
      /*to_path=*/kTextClassificationResourceId));

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act & Assert
  ASSERT_TRUE(base::test::RunUntil([this] { return !resource_->IsLoaded(); }));
}

TEST_F(CatsxpAdsTextClassificationResourceTest, DoNotLoadMissingResource) {
  // Arrange
  ON_CALL(ads_client_mock_, LoadResourceComponent(kTextClassificationResourceId,
                                                  /*version=*/::testing::_,
                                                  /*callback=*/::testing::_))
      .WillByDefault([](const std::string& /*id*/, int /*version*/,
                        LoadFileCallback callback) {
        const base::FilePath path =
            test::ResourceComponentsDataPath().AppendASCII(
                test::kMissingResourceId);

        base::File file(
            path, base::File::Flags::FLAG_OPEN | base::File::Flags::FLAG_READ);
        std::move(callback).Run(std::move(file));
      });

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotLoadResourceWithInvalidLanguageComponentId) {
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion,
      test::kInvalidLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotLoadResourceForNonRewardsUser) {
  // Arrange
  test::DisableCatsxpRewards();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotLoadResourceIfOptedOutOfAllAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotLoadResourceWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(
      ntp_background_images::prefs::kNewTabPageShowBackgroundImage, true);
  SetProfileBooleanPref(ntp_background_images::prefs::
                            kNewTabPageShowSponsoredImagesBackgroundImage,
                        true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       LoadResourceWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotResetResourceIfAlreadyOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();
  test::OptOutOfSearchResultAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       DoNotLoadResourceWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithInvalidLanguageComponentId) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion,
      test::kInvalidLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithExistingManifestVersion) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsTextClassificationResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithNewManifestVersion) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());
  ASSERT_EQ(test::kLanguageComponentManifestVersion,
            resource_->GetManifestVersion());

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersionUpdate,
      test::kLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
  EXPECT_EQ(test::kLanguageComponentManifestVersionUpdate,
            resource_->GetManifestVersion());
}

TEST_F(CatsxpAdsTextClassificationResourceTest,
       ResetResourceForOnNotifyDidUnregisterResourceComponent) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  ads_client_notifier_.NotifyDidUnregisterResourceComponent(
      test::kLanguageComponentId);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsTextClassificationResourceTest,
    DoNotResetResourceForOnNotifyDidUnregisterResourceComponentWithInvalidLanguageComponentId) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  ads_client_notifier_.NotifyDidUnregisterResourceComponent(
      test::kInvalidLanguageComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

}  // namespace catsxp_ads
