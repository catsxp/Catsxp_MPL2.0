/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_tab_helper.h"

#include <memory>

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "catsxp/components/catsxp_shields/core/common/pref_names.h"
#include "chrome/test/base/chrome_render_view_host_test_harness.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/favicon/content/content_favicon_driver.h"
#include "components/favicon/core/test/mock_favicon_service.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/test/navigation_simulator.h"
#include "content/public/test/test_renderer_host.h"
#include "content/public/test/web_contents_tester.h"
#include "content/test/test_web_contents.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace catsxp_shields {

namespace {

class MockCatsxpShieldsTabHelperObserver
    : public CatsxpShieldsTabHelper::Observer {
 public:
  MOCK_METHOD(void, OnResourcesChanged, (), (override));
  MOCK_METHOD(void, OnFaviconUpdated, (), (override));
  MOCK_METHOD(void, OnShieldsEnabledChanged, (), (override));
  MOCK_METHOD(void, OnShieldsAdBlockOnlyModeEnabledChanged, (), (override));
  MOCK_METHOD(void, OnRepeatedReloadsDetected, (), (override));
};

}  // namespace

class CatsxpShieldsTabHelperUnitTest
    : public content::RenderViewHostTestHarness {
 public:
  CatsxpShieldsTabHelperUnitTest()
      : content::RenderViewHostTestHarness(
            base::test::TaskEnvironment::TimeSource::MOCK_TIME) {}

  ~CatsxpShieldsTabHelperUnitTest() override = default;

  void SetUp() override {
    content::RenderViewHostTestHarness::SetUp();

    favicon::ContentFaviconDriver::CreateForWebContents(web_contents(),
                                                        &favicon_service_);
    CatsxpShieldsTabHelper::CreateForWebContents(web_contents());
    catsxp_shields_tab_helper_ =
        CatsxpShieldsTabHelper::FromWebContents(web_contents());
    observer_ = std::make_unique<
        testing::NiceMock<MockCatsxpShieldsTabHelperObserver>>();
    catsxp_shields_tab_helper_->AddObserver(observer_.get());

    TestingBrowserProcess::GetGlobal()->SetApplicationLocale("en-US");
  }

  void TearDown() override {
    catsxp_shields_tab_helper_->RemoveObserver(observer_.get());
    catsxp_shields_tab_helper_ = nullptr;
    content::RenderViewHostTestHarness::TearDown();
  }

  std::unique_ptr<content::BrowserContext> CreateBrowserContext() override {
    return std::make_unique<TestingProfile>();
  }

  void NavigateTo(GURL url) {
    content::NavigationSimulator::NavigateAndCommitFromBrowser(web_contents(),
                                                               url);
    EXPECT_EQ(web_contents()->GetLastCommittedURL(), url);
  }

  void Reload() { content::NavigationSimulator::Reload(web_contents()); }

  PrefService* profile_prefs() {
    return Profile::FromBrowserContext(web_contents()->GetBrowserContext())
        ->GetPrefs();
  }

  void SetApplicationLocale(const std::string& locale) {
    TestingBrowserProcess::GetGlobal()->SetApplicationLocale(locale);
  }

  PrefService* local_state() {
    return TestingBrowserProcess::GetGlobal()->GetTestingLocalState();
  }

 protected:
  testing::NiceMock<favicon::MockFaviconService> favicon_service_;
  std::unique_ptr<testing::NiceMock<MockCatsxpShieldsTabHelperObserver>>
      observer_;
  raw_ptr<CatsxpShieldsTabHelper> catsxp_shields_tab_helper_;
  base::test::ScopedFeatureList feature_list_;
};

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenFeatureDisabled) {
  feature_list_.InitAndDisableFeature(features::kAdblockOnlyMode);

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenLocaleNotSupported) {
  SetApplicationLocale("fr-FR");

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenAdBlockOnlyModeAlreadyEnabled) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });
  local_state()->SetBoolean(catsxp_shields::prefs::kAdBlockOnlyModeEnabled,
                            true);

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedOnNotReloadNavigation) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
  NavigateTo(GURL("https://example.com"));
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenReloadsByShieldsChanges) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(true);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(true);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedByZeroCountFeatureParameters) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "0"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "0"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
}

TEST_F(CatsxpShieldsTabHelperUnitTest, TriggerOnRepeatedReloadsDetected) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(2);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
  testing::Mock::VerifyAndClearExpectations(observer_.get());

  // Counter is reset after more than
  // `kAdblockOnlyModePromptAfterPageReloadsInterval` time interval. Fast
  // forward by 2 times to ensure the counter is reset.
  task_environment()->FastForwardBy(
      2 * features::kAdblockOnlyModePromptAfterPageReloadsInterval.Get());

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(2);
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
  testing::Mock::VerifyAndClearExpectations(observer_.get());
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontTriggerOnRepeatedReloadsDetectedWhenPromptDismissed) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterPageReloadsMin.name, "1"},
          {features::kAdblockOnlyModePromptAfterPageReloadsMax.name, "2"},
          {features::kAdblockOnlyModePromptAfterPageReloadsInterval.name, "1s"},
      });
  catsxp_shields_tab_helper_->SetCatsxpShieldsAdBlockOnlyModePromptDismissed();

  EXPECT_CALL(*observer_, OnRepeatedReloadsDetected).Times(0);

  NavigateTo(GURL("https://example.com"));
  Reload();
  Reload();
  Reload();
  Reload();
  Reload();
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenFeatureDisabled) {
  feature_list_.InitAndDisableFeature(features::kAdblockOnlyMode);

  // Default value of
  // `features::kAdblockOnlyModePromptAfterShieldsDisabledCount` is 5.
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);

  EXPECT_EQ(
      profile_prefs()->GetInteger(catsxp_shields::prefs::kShieldsDisabledCount),
      0);

  EXPECT_FALSE(catsxp_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenLocaleNotSupported) {
  SetApplicationLocale("fr-FR");

  // Default value of
  // `features::kAdblockOnlyModePromptAfterShieldsDisabledCount` is 5.
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);

  EXPECT_EQ(
      profile_prefs()->GetInteger(catsxp_shields::prefs::kShieldsDisabledCount),
      0);

  EXPECT_FALSE(catsxp_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       DontShowShieldsDisabledAdBlockOnlyModePromptWhenPromptDismissed) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterShieldsDisabledCount.name, "2"},
      });
  catsxp_shields_tab_helper_->SetCatsxpShieldsAdBlockOnlyModePromptDismissed();

  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  EXPECT_FALSE(catsxp_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

TEST_F(CatsxpShieldsTabHelperUnitTest,
       ShowShieldsDisabledAdBlockOnlyModePrompt) {
  feature_list_.InitAndEnableFeatureWithParameters(
      features::kAdblockOnlyMode,
      {
          {features::kAdblockOnlyModePromptAfterShieldsDisabledCount.name, "2"},
      });

  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  EXPECT_FALSE(catsxp_shields_tab_helper_
                   ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());

  catsxp_shields_tab_helper_->SetCatsxpShieldsEnabled(false);
  EXPECT_TRUE(catsxp_shields_tab_helper_
                  ->ShouldShowShieldsDisabledAdBlockOnlyModePrompt());
}

}  // namespace catsxp_shields
