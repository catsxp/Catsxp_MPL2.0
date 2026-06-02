/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_processor.h"

#include <memory>

#include "base/test/run_until.h"
#include "catsxp/components/catsxp_ads/core/internal/common/resources/test/language_components_test_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/deprecated/client/client_state_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_types.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTextClassificationProcessorTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<TextClassificationResource>();
  }

  std::unique_ptr<TextClassificationResource> resource_;
};

TEST_F(CatsxpAdsTextClassificationProcessorTest,
       DoNotProcessIfResourceIsNotInitialized) {
  // Arrange
  TextClassificationProcessor processor(*resource_);

  // Act
  processor.Process(/*text=*/"The quick brown fox jumps over the lazy dog");

  // Assert
  const TextClassificationProbabilityList& text_classification_probabilities =
      ClientStateManager::GetInstance()
          .GetTextClassificationProbabilitiesHistory();
  EXPECT_THAT(text_classification_probabilities, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTextClassificationProcessorTest, DoNotProcessForEmptyText) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  TextClassificationProcessor processor(*resource_);

  // Act
  processor.Process(/*text=*/"");

  // Assert
  const TextClassificationProbabilityList& text_classification_probabilities =
      ClientStateManager::GetInstance()
          .GetTextClassificationProbabilitiesHistory();
  EXPECT_THAT(text_classification_probabilities, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTextClassificationProcessorTest, NeverProcessed) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act & Assert
  const TextClassificationProbabilityList& text_classification_probabilities =
      ClientStateManager::GetInstance()
          .GetTextClassificationProbabilitiesHistory();
  EXPECT_THAT(text_classification_probabilities, ::testing::IsEmpty());
}

TEST_F(CatsxpAdsTextClassificationProcessorTest, ProcessText) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  TextClassificationProcessor processor(*resource_);

  // Act
  processor.Process(/*text=*/"Some content about technology & computing");

  // Assert
  ASSERT_TRUE(base::test::RunUntil([&] {
    return ClientStateManager::GetInstance()
               .GetTextClassificationProbabilitiesHistory()
               .size() == 1U;
  }));
  const TextClassificationProbabilityList& text_classification_probabilities =
      ClientStateManager::GetInstance()
          .GetTextClassificationProbabilitiesHistory();
  EXPECT_THAT(text_classification_probabilities, ::testing::SizeIs(1));
}

TEST_F(CatsxpAdsTextClassificationProcessorTest, ProcessMultipleText) {
  // Arrange
  ads_client_notifier_.NotifyResourceComponentDidChange(
      test::kLanguageComponentManifestVersion, test::kLanguageComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  TextClassificationProcessor processor(*resource_);

  // Act
  processor.Process(/*text=*/"Some content about cooking food");
  processor.Process(/*text=*/"Some content about finance & banking");
  processor.Process(/*text=*/"Some content about technology & computing");

  // Assert
  ASSERT_TRUE(base::test::RunUntil([&] {
    return ClientStateManager::GetInstance()
               .GetTextClassificationProbabilitiesHistory()
               .size() == 3U;
  }));
  const TextClassificationProbabilityList& text_classification_probabilities =
      ClientStateManager::GetInstance()
          .GetTextClassificationProbabilitiesHistory();
  EXPECT_THAT(text_classification_probabilities, ::testing::SizeIs(3));
}

}  // namespace catsxp_ads
