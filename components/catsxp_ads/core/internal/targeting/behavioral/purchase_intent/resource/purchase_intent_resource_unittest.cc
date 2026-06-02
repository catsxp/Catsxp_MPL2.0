/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"

#include <memory>
#include <utility>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/test/run_until.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/country_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/resource_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/file_path_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/test/settings_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource_constants.h"
#include "catsxp/components/catsxp_ads/core/public/prefs/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsPurchaseIntentResourceTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<PurchaseIntentResource>();
  }

  std::unique_ptr<PurchaseIntentResource> resource_;
};

TEST_F(CatsxpAdsPurchaseIntentResourceTest, IsResourceNotLoaded) {
  // Act & Assert
  EXPECT_FALSE(resource_->GetManifestVersion());
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest, LoadResource) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);

  // Act & Assert
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest, DoNotLoadMalformedResource) {
  // Arrange
  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      /*from_path=*/test::kMalformedResourceId,
      /*to_path=*/kPurchaseIntentResourceId));

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(resource_->GetManifestVersion());

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest, DoNotLoadMissingResource) {
  // Arrange
  ON_CALL(ads_client_mock_, LoadResourceComponent(kPurchaseIntentResourceId,
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
      test::kCountryComponentManifestVersion, test::kCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWithInvalidCountryComponentId) {
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kInvalidCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       DoNotLoadResourceIfOptedOutOfAllAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);

  // Act & Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWhenOptingInToNewTabPageAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
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

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       LoadResourceWhenOptingInToNotificationAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       DoNotResetResourceIfAlreadyOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();
  test::OptOutOfSearchResultAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  SetProfileBooleanPref(prefs::kOptedInToNotificationAds, true);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       DoNotLoadResourceWhenOptingInToSearchResultAds) {
  // Arrange
  test::OptOutOfAllAds();

  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_FALSE(resource_->IsLoaded());

  // Act
  SetProfileBooleanPref(prefs::kOptedInToSearchResultAds, true);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithInvalidCountryComponentId) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kInvalidCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithExistingManifestVersion) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnResourceComponentDidChangeWithNewManifestVersion) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));
  ASSERT_EQ(test::kCountryComponentManifestVersion,
            resource_->GetManifestVersion());

  // Act
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersionUpdate, test::kCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
  EXPECT_EQ(test::kCountryComponentManifestVersionUpdate,
            resource_->GetManifestVersion());
}

TEST_F(CatsxpAdsPurchaseIntentResourceTest,
       ResetResourceForOnNotifyDidUnregisterResourceComponent) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  ads_client_notifier_.NotifyDidUnregisterResourceComponent(
      test::kCountryComponentId);

  // Assert
  EXPECT_FALSE(resource_->IsLoaded());
}

TEST_F(
    CatsxpAdsPurchaseIntentResourceTest,
    DoNotResetResourceForOnNotifyDidUnregisterResourceComponentWithInvalidCountryComponentId) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kCountryComponentManifestVersion, test::kCountryComponentId);
  ASSERT_TRUE(base::test::RunUntil([this] { return resource_->IsLoaded(); }));

  // Act
  ads_client_notifier_.NotifyDidUnregisterResourceComponent(
      test::kInvalidCountryComponentId);

  // Assert
  EXPECT_TRUE(resource_->IsLoaded());
}

}  // namespace catsxp_ads
