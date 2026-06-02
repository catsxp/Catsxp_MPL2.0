/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/new_tab/new_tab_shows_options.h"
#include "catsxp/components/constants/pref_names.h"
#include "catsxp/components/constants/webui_url_constants.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/prefs/pref_service.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/url_constants.h"

class CatsxpNewTabTest : public testing::Test {
 public:
  CatsxpNewTabTest() : manager_(TestingBrowserProcess::GetGlobal()) {}
  ~CatsxpNewTabTest() override = default;

 protected:
  void SetUp() override {
    ASSERT_TRUE(manager_.SetUp());
  }

  TestingProfileManager* manager() { return &manager_; }

 private:
  content::BrowserTaskEnvironment task_environment_;
  TestingProfileManager manager_;
};

TEST_F(CatsxpNewTabTest, BasicTest) {
  Profile* profile = manager()->CreateTestingProfile("Test 1");
  Profile* otr_profile =
      profile->GetPrimaryOTRProfile(/*create_if_needed=*/true);
  ASSERT_TRUE(profile);
  ASSERT_TRUE(otr_profile);

  auto* prefs = profile->GetPrefs();

  // Check NTP url is empty for DASHBOARD.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(catsxp::NewTabPageShowsOptions::kDashboard));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(catsxp::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(catsxp::ShouldNewTabShowDashboard(profile));

  // Check NTP url is empty when option is HOMEPAGE and kHomePageIsNewTabPage
  // is true.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(catsxp::NewTabPageShowsOptions::kHomepage));
  prefs->SetString(prefs::kHomePage, "https://www.catsxp.com/");
  prefs->SetBoolean(prefs::kHomePageIsNewTabPage, true);
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(catsxp::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(catsxp::ShouldNewTabShowDashboard(profile));

  // Check NTP url is configured url when option is HOMEPAGE and
  // kHomePageIsNewTabPage is false.
  prefs->SetBoolean(prefs::kHomePageIsNewTabPage, false);
  EXPECT_EQ(GURL("https://www.catsxp.com/"), catsxp::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(otr_profile));
  EXPECT_FALSE(catsxp::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_FALSE(catsxp::ShouldNewTabShowDashboard(profile));

  // If homepage url is newtab url, dashboard settings should be shown.
  prefs->SetString(prefs::kHomePage, "chrome://newtab/");
  EXPECT_TRUE(catsxp::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_TRUE(catsxp::ShouldNewTabShowDashboard(profile));

  // Check NTP url is used when option is BLANKPAGE.
  // Blank page will go NTP route and CatsxpNewTabUI will handle it.
  prefs->SetInteger(
      kNewTabPageShowsOptions,
      static_cast<int>(catsxp::NewTabPageShowsOptions::kBlankpage));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(profile));
  EXPECT_EQ(GURL(), catsxp::GetNewTabPageURL(otr_profile));
  EXPECT_TRUE(catsxp::ShouldUseNewTabURLForNewTab(profile));
  EXPECT_FALSE(catsxp::ShouldNewTabShowDashboard(profile));
  EXPECT_TRUE(catsxp::ShouldNewTabShowBlankpage(profile));
  EXPECT_FALSE(catsxp::ShouldNewTabShowBlankpage(otr_profile));
}
