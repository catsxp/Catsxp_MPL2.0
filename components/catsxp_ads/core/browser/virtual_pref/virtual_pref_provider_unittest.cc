/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/virtual_pref/virtual_pref_provider.h"

#include <memory>
#include <utility>

#include "base/memory/raw_ptr.h"
#include "base/test/values_test_util.h"
#include "base/values.h"
#include "base/version_info/version_info.h"
#include "catsxp/components/catsxp_ads/core/browser/virtual_pref/test/virtual_pref_provider_delegate_mock.h"
#include "catsxp/components/catsxp_ads/core/internal/common/locale/test/fake_locale.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/ntp_background_images/common/pref_names.h"
#include "catsxp/components/skus/browser/pref_names.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsVirtualPrefProviderTest : public ::testing::Test {
 public:
  CatsxpAdsVirtualPrefProviderTest() {
    prefs_.registry()->RegisterBooleanPref(
        ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist,
        true);
    prefs_.registry()->RegisterBooleanPref(
        catsxp_rewards::prefs::kDisabledByPolicy, false);
    local_state_.registry()->RegisterDictionaryPref(skus::prefs::kSkusState);

    auto delegate = std::make_unique<VirtualPrefProviderDelegateMock>();
    delegate_ = delegate.get();
    provider_ = std::make_unique<VirtualPrefProvider>(prefs_, local_state_,
                                                      std::move(delegate));
  }

  ~CatsxpAdsVirtualPrefProviderTest() override {
    // Reset delegate to avoid dangling pointer.
    delegate_ = nullptr;
  }

  base::DictValue GetVirtualPrefs() const { return provider_->GetPrefs(); }

 protected:
  test::FakeLocale fake_locale_;

  TestingPrefServiceSimple prefs_;
  TestingPrefServiceSimple local_state_;

  std::unique_ptr<VirtualPrefProvider> provider_;

  raw_ptr<VirtualPrefProviderDelegateMock> delegate_ = nullptr;
};

TEST_F(CatsxpAdsVirtualPrefProviderTest, BrowserBuildChannel) {
  // Arrange
  EXPECT_CALL(*delegate_, GetChannel).WillOnce(testing::Return("release"));

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const build_channel =
      virtual_prefs.FindStringByDottedPath("[virtual]:browser.build_channel");
  ASSERT_TRUE(build_channel);
  EXPECT_EQ(*build_channel, "release");
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, BrowserVersion) {
  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const version =
      virtual_prefs.FindStringByDottedPath("[virtual]:browser.version");
  ASSERT_TRUE(version);
  EXPECT_EQ(*version, version_info::GetVersionNumber());
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, OperatingSystemLocaleLanguage) {
  // Arrange
  fake_locale_.SetLanguageCode("en");

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const language = virtual_prefs.FindStringByDottedPath(
      "[virtual]:operating_system.locale.language");
  ASSERT_TRUE(language);
  EXPECT_EQ(*language, "en");
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, OperatingSystemLocaleRegion) {
  // Arrange
  fake_locale_.SetCountryCode("KY");

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const region = virtual_prefs.FindStringByDottedPath(
      "[virtual]:operating_system.locale.region");
  ASSERT_TRUE(region);
  EXPECT_EQ(*region, "KY");
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, OperatingSystemName) {
  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const name =
      virtual_prefs.FindStringByDottedPath("[virtual]:operating_system.name");
  ASSERT_TRUE(name);
  EXPECT_EQ(*name, version_info::GetOSType());
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, IsSurveyPanelist) {
  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  EXPECT_TRUE(
      virtual_prefs.FindBoolByDottedPath("[virtual]:is_survey_panelist"));
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, SearchEngineDefaultName) {
  // Arrange
  EXPECT_CALL(*delegate_, GetDefaultSearchEngineName)
      .WillOnce(testing::Return("Catsxp"));

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const auto* const default_search_engine_name =
      virtual_prefs.FindStringByDottedPath(
          "[virtual]:search_engine.default_name");
  ASSERT_TRUE(default_search_engine_name);
  EXPECT_EQ(*default_search_engine_name, "Catsxp");
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, SerpMetrics) {
  // Arrange
  EXPECT_CALL(*delegate_, GetSerpMetrics)
      .WillOnce(testing::Return(base::test::ParseJsonDict(
          R"JSON({
            "catsxp_search_engine": [
              {"day": 1773291600.0, "value": 3.0}
            ],
            "google_search_engine": [
              {"day": 1773291600.0, "value": 7.0}
            ],
            "other_search_engine": [
              {"day": 1773291600.0, "value": 2.0}
            ]
          })JSON")));

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const base::DictValue expected_serp_metrics = base::test::ParseJsonDict(
      R"JSON({
        "catsxp_search_engine": [
          {"day": 1773291600.0, "value": 3.0}
        ],
        "google_search_engine": [
          {"day": 1773291600.0, "value": 7.0}
        ],
        "other_search_engine": [
          {"day": 1773291600.0, "value": 2.0}
        ]
      })JSON");
  const auto* const serp_metrics =
      virtual_prefs.FindDict("[virtual]:serp_metrics");
  ASSERT_TRUE(serp_metrics);
  EXPECT_EQ(*serp_metrics, expected_serp_metrics);
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, EmptySerpMetrics) {
  // Arrange
  EXPECT_CALL(*delegate_, GetSerpMetrics)
      .WillOnce(testing::Return(base::DictValue{}));

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  EXPECT_THAT(virtual_prefs.FindDict("[virtual]:serp_metrics"),
              testing::Pointee(testing::IsEmpty()));
}

TEST_F(CatsxpAdsVirtualPrefProviderTest, Skus) {
  // Arrange
  local_state_.SetDict(skus::prefs::kSkusState,
                       base::DictValue().Set("skus:development", R"JSON({
      "orders": {
        "f24787ab-7bc3-46b9-bc05-65befb360cb8": {
          "created_at": "2023-10-24T16:00:57.902289",
          "expires_at": "2023-12-24T17:03:59.030987",
          "last_paid_at": "2023-11-24T17:03:59.030987",
          "location": "leo.catsxp.com",
          "status": "paid"
        }
      }
    })JSON"));

  // Act
  const base::DictValue virtual_prefs = GetVirtualPrefs();

  // Assert
  const base::DictValue expected_skus = base::test::ParseJsonDict(
      R"JSON(
        {
          "development": {
            "leo.catsxp.com": {
                "created_at": "2023-10-24T16:00:57.902289",
                "expires_at": "2023-12-24T17:03:59.030987",
                "last_paid_at": "2023-11-24T17:03:59.030987",
                "status": "paid"
            }
          }
        })JSON");
  const auto* const skus = virtual_prefs.FindDict("[virtual]:skus");
  ASSERT_TRUE(skus);
  EXPECT_EQ(*skus, expected_skus);
}

}  // namespace catsxp_ads
