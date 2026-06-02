/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"

#include <memory>
#include <utility>

#include "base/files/scoped_temp_dir.h"
#include "base/test/scoped_feature_list.h"
#include "catsxp/browser/profiles/catsxp_profile_manager.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_p3a.h"
#include "catsxp/components/catsxp_shields/core/common/catsxp_shield_utils.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "catsxp/components/constants/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/cookie_settings_factory.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/content_settings/core/browser/cookie_settings.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/content_settings/core/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "content/public/test/test_utils.h"
#include "net/base/features.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using catsxp_shields::ControlType;
using catsxp_shields::ControlTypeFromString;
using catsxp_shields::ControlTypeToString;
using catsxp_shields::DomainBlockingType;
using catsxp_shields::GetPatternFromURL;
using catsxp_shields::features::kCatsxpDomainBlock;

class CatsxpShieldsUtilTest : public testing::Test {
 public:
  CatsxpShieldsUtilTest() = default;
  CatsxpShieldsUtilTest(const CatsxpShieldsUtilTest&) = delete;
  CatsxpShieldsUtilTest& operator=(const CatsxpShieldsUtilTest&) = delete;
  ~CatsxpShieldsUtilTest() override = default;

  void SetUp() override {
    ASSERT_TRUE(temp_dir_.CreateUniqueTempDir());
    TestingBrowserProcess::GetGlobal()->SetProfileManager(
        CreateProfileManagerForTest());
    TestingProfile::Builder builder;
    builder.SetPath(temp_dir_.GetPath());
    profile_ = builder.Build();
    g_browser_process->profile_manager()->InitProfileUserPrefs(profile_.get());
  }

  void TearDown() override {
    profile_.reset();
    TestingBrowserProcess::GetGlobal()->SetProfileManager(nullptr);
    content::RunAllTasksUntilIdle();
  }

  TestingProfile* profile() { return profile_.get(); }

  void ExpectDomainBlockingType(const GURL& url,
                                DomainBlockingType domain_blocking_type) {
    auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
    auto setting = catsxp_shields::GetDomainBlockingType(map, url);
    EXPECT_EQ(domain_blocking_type, setting);
  }

 private:
  std::unique_ptr<CatsxpProfileManager> CreateProfileManagerForTest() {
    return std::make_unique<CatsxpProfileManagerWithoutInit>(
        temp_dir_.GetPath());
  }

  base::ScopedTempDir temp_dir_;
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<TestingProfile> profile_;
};

class CatsxpShieldsUtilDomainBlockFeatureTest : public CatsxpShieldsUtilTest {
 public:
  CatsxpShieldsUtilDomainBlockFeatureTest() {
    feature_list_.InitAndDisableFeature(kCatsxpDomainBlock);
  }

 private:
  base::test::ScopedFeatureList feature_list_;
};

TEST_F(CatsxpShieldsUtilTest, GetPatternFromURL) {
  // wildcard
  auto pattern = GetPatternFromURL(GURL());
  EXPECT_EQ(ContentSettingsPattern::Wildcard(), pattern);

  // scheme is a wildcard, should match any scheme
  pattern = GetPatternFromURL(GURL("http://catsxp.com"));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("https://catsxp.com")));
  EXPECT_TRUE(pattern.Matches(GURL("ftp://catsxp.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.catsxp.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://catsxp2.com")));

  // path is a wildcard
  pattern = GetPatternFromURL(GURL("http://catsxp.com/path1"));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com/path2")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.catsxp.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://catsxp2.com")));

  // port is a wildcard
  pattern = GetPatternFromURL(GURL("http://catsxp.com:8080"));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com:8080")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com:8080/path1")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com:8080/path2")));
  EXPECT_TRUE(pattern.Matches(GURL("http://catsxp.com:5555")));
  EXPECT_TRUE(pattern.Matches(GURL("https://catsxp.com")));
  EXPECT_TRUE(pattern.Matches(GURL("https://catsxp.com:8080")));
  EXPECT_FALSE(pattern.Matches(GURL("http://subdomain.catsxp.com")));
  EXPECT_FALSE(pattern.Matches(GURL("http://catsxp2.com")));

  // with implied port
  pattern = GetPatternFromURL(GURL("https://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  pattern = GetPatternFromURL(GURL("http://brianbondy.com"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
  // with specified port
  pattern = GetPatternFromURL(GURL("http://brianbondy.com:8080"));
  EXPECT_EQ(pattern.ToString(), "brianbondy.com");
}

TEST_F(CatsxpShieldsUtilTest, ControlTypeToString) {
  EXPECT_EQ("block", ControlTypeToString(ControlType::BLOCK));
  EXPECT_EQ("allow", ControlTypeToString(ControlType::ALLOW));
  EXPECT_EQ("block_third_party",
            ControlTypeToString(ControlType::BLOCK_THIRD_PARTY));
}

TEST_F(CatsxpShieldsUtilTest, ControlTypeFromString) {
  EXPECT_EQ(ControlType::BLOCK, ControlTypeFromString("block"));
  EXPECT_EQ(ControlType::ALLOW, ControlTypeFromString("allow"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            ControlTypeFromString("block_third_party"));
}

/* CATSXP_SHIELDS CONTROL */
TEST_F(CatsxpShieldsUtilTest, SetCatsxpShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  catsxp_shields::SetCatsxpShieldsEnabled(map, false, GURL("http://catsxp.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                        ContentSettingsType::CATSXP_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should apply to different scheme
  setting = map->GetContentSetting(GURL("https://catsxp.com"), GURL(),
                                   ContentSettingsType::CATSXP_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should not apply to default
  setting = map->GetContentSetting(GURL(), GURL(),
                                   ContentSettingsType::CATSXP_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  GURL host2("http://host2.com");
  GURL host1("http://host1.com");
  // Set shields as disabled for initial value.
  catsxp_shields::SetCatsxpShieldsEnabled(map, false, host1);
  // host2.com is enabled by default
  setting =
      map->GetContentSetting(host2, GURL(), ContentSettingsType::CATSXP_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // Set policy to disable shields for specific domain.
  base::ListValue disabled_list;
  disabled_list.Append("[*.]host2.com");
  disabled_list.Append("*.*");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedCatsxpShieldsDisabledForUrls, std::move(disabled_list));

  base::ListValue enabled_list;
  enabled_list.Append("[*.]host1.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedCatsxpShieldsEnabledForUrls, std::move(enabled_list));

  // setting should apply block to origin.
  setting =
      map->GetContentSetting(host2, GURL(), ContentSettingsType::CATSXP_SHIELDS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  catsxp_shields::SetCatsxpShieldsEnabled(map, true, host2);

  // setting should not be changed.
  EXPECT_FALSE(catsxp_shields::GetCatsxpShieldsEnabled(map, host2));

  // setting should apply enabled to origin.
  EXPECT_TRUE(catsxp_shields::GetCatsxpShieldsEnabled(map, host1));
  catsxp_shields::SetCatsxpShieldsEnabled(map, false, host1);
  // setting should not be changed.
  EXPECT_TRUE(catsxp_shields::GetCatsxpShieldsEnabled(map, host1));

  // setting should not apply to default
  EXPECT_TRUE(catsxp_shields::GetCatsxpShieldsEnabled(map, GURL()));
}

TEST_F(CatsxpShieldsUtilTest, IsCatsxpShieldsManaged) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  GURL host2("http://host2.com");
  GURL host1("http://host1.com");
  EXPECT_FALSE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  base::ListValue disabled_list;
  disabled_list.Append("[*.]host2.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedCatsxpShieldsDisabledForUrls, std::move(disabled_list));
  // only disabled pref set
  EXPECT_TRUE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_FALSE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, GURL("http://host1.com")));

  base::ListValue enabled_list;
  enabled_list.Append("[*.]host1.com");
  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedCatsxpShieldsEnabledForUrls, std::move(enabled_list));

  // both disabled/enabled prefs set
  EXPECT_TRUE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_TRUE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host1));

  profile()->GetTestingPrefService()->RemoveManagedPref(
      kManagedCatsxpShieldsDisabledForUrls);

  // only enabled prefs set
  EXPECT_FALSE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host2));

  EXPECT_TRUE(catsxp_shields::IsCatsxpShieldsManaged(
      profile()->GetTestingPrefService(), map, host1));
}

TEST_F(CatsxpShieldsUtilTest, SetCatsxpShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);
  catsxp_shields::SetCatsxpShieldsEnabled(map, ControlType::ALLOW,
                                        GURL("chrome://preferences"));
  setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
  catsxp_shields::SetCatsxpShieldsEnabled(map, ControlType::ALLOW,
                                        GURL("about:blank"));
  setting = catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetCatsxpShieldsEnabled_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetCatsxpShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
  setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("http://catsxp.com"));
  EXPECT_EQ(true, setting);
  setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("https://catsxp.com"));
  EXPECT_EQ(true, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://catsxp.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);
  setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("http://catsxp.com/*"));
  EXPECT_EQ(false, setting);
  // https in unchanged
  setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("https://catsxp.com"));
  EXPECT_EQ(true, setting);
  // default is unchanged
  setting = catsxp_shields::GetCatsxpShieldsEnabled(map, GURL());
  EXPECT_EQ(true, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetCatsxpShieldsEnabled_IsNotHttpHttps) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto setting =
      catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("chrome://preferences"));
  EXPECT_EQ(false, setting);

  setting = catsxp_shields::GetCatsxpShieldsEnabled(map, GURL("about:blank"));
  EXPECT_EQ(false, setting);
}

/* AD CONTROL */
TEST_F(CatsxpShieldsUtilTest, SetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* ALLOW */
  catsxp_shields::SetAdControlType(map, ControlType::ALLOW, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  catsxp_shields::SetAdControlType(map, ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(CatsxpShieldsUtilTest, SetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  catsxp_shields::SetAdControlType(map, ControlType::ALLOW,
                                  GURL("http://catsxp.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                        ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://catsxp.com"), GURL(),
                                   ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::CATSXP_ADS);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetAdControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::CATSXP_ADS, CONTENT_SETTING_ALLOW);
  setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::CATSXP_ADS, CONTENT_SETTING_BLOCK);
  setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetAdControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = catsxp_shields::GetAdControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://catsxp.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_ADS,
      CONTENT_SETTING_ALLOW);
  setting = catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting = catsxp_shields::GetAdControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK */
  // change default to allow
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::CATSXP_ADS, CONTENT_SETTING_ALLOW);
  setting = catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = catsxp_shields::GetAdControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://catsxp.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_ADS,
      CONTENT_SETTING_BLOCK);
  setting = catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting = catsxp_shields::GetAdControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = catsxp_shields::GetAdControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetAdControlType_ManagedPref) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCatsxpAdblockSetting,
      base::Value(CONTENT_SETTING_ALLOW));
  EXPECT_EQ(ControlType::ALLOW, catsxp_shields::GetAdControlType(map, GURL()));
  EXPECT_EQ(ControlType::ALLOW,
            catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com")));

  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCatsxpAdblockSetting,
      base::Value(CONTENT_SETTING_BLOCK));
  EXPECT_EQ(ControlType::BLOCK, catsxp_shields::GetAdControlType(map, GURL()));
  EXPECT_EQ(ControlType::BLOCK,
            catsxp_shields::GetAdControlType(map, GURL("http://catsxp.com")));
}

/* COOKIE CONTROL */
TEST_F(CatsxpShieldsUtilTest, SetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());
  /* ALLOW */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::ALLOW, GURL());
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_FALSE(cookies->ShouldBlockThirdPartyCookies());
  setting =
      map->GetContentSetting(GURL("http://catsxp.com"), GURL("http://catsxp.com"),
                             ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://catsxp.com"),
                                   GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // Ensure BLOCK with kCookieControlsMode == kOff still blocks all cookies.
  profile()->GetPrefs()->SetInteger(
      ::prefs::kCookieControlsMode,
      static_cast<int>(content_settings::CookieControlsMode::kOff));
  EXPECT_FALSE(cookies->ShouldBlockThirdPartyCookies());
  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);
  setting = map->GetContentSetting(GURL("http://catsxp.com"),
                                   GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  setting = map->GetContentSetting(GURL(), GURL("https://firstParty"),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // setting should apply to all urls
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
  setting =
      map->GetContentSetting(GURL("http://catsxp.com"), GURL("http://catsxp.com"),
                             ContentSettingsType::COOKIES);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  EXPECT_TRUE(cookies->ShouldBlockThirdPartyCookies());
}

TEST_F(CatsxpShieldsUtilTest, SetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  catsxp_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://catsxp.com"));
  // override should apply to origin
  auto setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // override should also apply to different scheme
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetCookieControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  EXPECT_EQ(CONTENT_SETTING_ALLOW,
            map->GetContentSetting(GURL::EmptyGURL(), GURL::EmptyGURL(),
                                   ContentSettingsType::CATSXP_COOKIES));
  auto setting =
      catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::ALLOW, GURL());
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* BLOCK_THIRD_PARTY */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  // Setting CONTENT_SETTING_DEFAULT doesn't produce any CHECKS or crashes.
  map->SetDefaultContentSetting(ContentSettingsType::CATSXP_COOKIES,
                                CONTENT_SETTING_DEFAULT);
}

TEST_F(CatsxpShieldsUtilTest, GetCookieControlType_WithUserSettings) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  struct CookieState {
    bool block_first_party = false;
    bool block_third_party = false;
  };

  auto get_effective_cookie_state =
      [](content_settings::CookieSettings* cookie_settings,
         const GURL& url) -> CookieState {
    const auto first_party_blocked =
        cookie_settings->GetCookieSetting(
            url, net::SiteForCookies::FromUrl(url), url,
            net::CookieSettingOverrides(), nullptr) == CONTENT_SETTING_BLOCK;

    const auto third_party_blocked =
        cookie_settings->GetCookieSetting(
            GURL::EmptyGURL(), net::SiteForCookies(), url,
            net::CookieSettingOverrides(), nullptr) == CONTENT_SETTING_BLOCK;

    return {first_party_blocked, third_party_blocked};
  };

  auto cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://catsxp.com"));
  EXPECT_FALSE(cookies_settings.block_first_party);
  EXPECT_TRUE(cookies_settings.block_third_party);

  // block all
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(),
      ContentSettingsPattern::FromURL(GURL("http://catsxp.com")),
      ContentSettingsType::COOKIES, CONTENT_SETTING_BLOCK);

  auto setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://catsxp.com"));
  // User settings doesn't affect CATSXP_COOKIES
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://catsxp.com"));
  EXPECT_TRUE(cookies_settings.block_first_party);
  EXPECT_TRUE(cookies_settings.block_third_party);

  catsxp_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://catsxp.com"));
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  // User settings still doesn't affect CATSXP_COOKIES
  EXPECT_EQ(ControlType::ALLOW, setting);

  cookies_settings =
      get_effective_cookie_state(cookies.get(), GURL("http://catsxp.com"));
  EXPECT_FALSE(cookies_settings.block_first_party);
  EXPECT_FALSE(cookies_settings.block_third_party);
}

TEST_F(CatsxpShieldsUtilTest, GetCookieControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* ALLOW */
  catsxp_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::ALLOW, GURL("http://catsxp.com"));
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK */
  catsxp_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::BLOCK, GURL("http://catsxp.com"));
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);

  /* BLOCK_THIRD_PARTY */
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY,
                                      GURL("http://catsxp.com"));
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
  setting = catsxp_shields::GetCookieControlType(map, cookies.get(), GURL());
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY, setting);
}

TEST_F(CatsxpShieldsUtilTest,
       GetCookieControlType_ManagedPrefOverridesBlockAllCookies) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  // Set initial value to block all cookies.
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK, GURL());
  catsxp_shields::SetCookieControlType(
      map, profile()->GetPrefs(), ControlType::BLOCK, GURL("http://catsxp.com"));

  // Set policy to allow cookies.
  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCookiesSetting, base::Value(CONTENT_SETTING_ALLOW));

  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            catsxp_shields::GetCookieControlType(map, cookies.get(), GURL()));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com")));
}

TEST_F(CatsxpShieldsUtilTest,
       GetCookieControlType_ManagedPrefOverridesBlockThirdPartyCookies) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  auto cookies = CookieSettingsFactory::GetForProfile(profile());

  // Set initial value to block third party cookies.
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY, GURL());
  catsxp_shields::SetCookieControlType(map, profile()->GetPrefs(),
                                      ControlType::BLOCK_THIRD_PARTY,
                                      GURL("http://catsxp.com"));

  // Set policy to block all cookies.
  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCookiesSetting, base::Value(CONTENT_SETTING_BLOCK));

  EXPECT_EQ(ControlType::BLOCK,
            catsxp_shields::GetCookieControlType(map, cookies.get(), GURL()));
  EXPECT_EQ(ControlType::BLOCK,
            catsxp_shields::GetCookieControlType(map, cookies.get(),
                                                GURL("http://catsxp.com")));
}

/* FINGERPRINTING CONTROL */
TEST_F(CatsxpShieldsUtilTest, SetFingerprintingControlType_Default) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      catsxp_shields::features::kCatsxpShowStrictFingerprintingMode);

  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // setting should be default to start with
  auto type = catsxp_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* ALLOW */
  catsxp_shields::SetFingerprintingControlType(map, ControlType::ALLOW, GURL());
  type = catsxp_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, type);

  // setting should apply to all urls
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  /* BLOCK */
  catsxp_shields::SetFingerprintingControlType(map, ControlType::BLOCK, GURL());
  type = catsxp_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, type);

  // setting should apply to all urls
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  /* DEFAULT */
  catsxp_shields::SetFingerprintingControlType(map, ControlType::DEFAULT,
                                              GURL());
  type = catsxp_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);

  // setting should apply to all urls
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global ALLOW and Site explicit DEFAULT */
  catsxp_shields::SetFingerprintingControlType(map, ControlType::ALLOW, GURL());
  catsxp_shields::SetFingerprintingControlType(map, ControlType::DEFAULT,
                                              GURL("http://catsxp.com"));
  // Site should have DEFAULT if it's explicitly set.
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);

  /* Global BLOCK and Site explicit DEFAULT */
  catsxp_shields::SetFingerprintingControlType(map, ControlType::BLOCK, GURL());
  // Site should have DEFAULT if it's explicitly set.
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::DEFAULT, type);
}

TEST_F(CatsxpShieldsUtilTest, SetFingerprintingControlType_ForOrigin) {
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      catsxp_shields::features::kCatsxpShowStrictFingerprintingMode);

  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  catsxp_shields::SetFingerprintingControlType(map, ControlType::ALLOW,
                                              GURL("http://catsxp.com"));
  auto type = catsxp_shields::GetFingerprintingControlType(
      map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, type);
  // override should also apply to different scheme
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, type);

  catsxp_shields::SetFingerprintingControlType(map, ControlType::BLOCK,
                                              GURL("http://catsxp.com"));
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, type);
  // override should also apply to different scheme
  type = catsxp_shields::GetFingerprintingControlType(map,
                                                     GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, type);

  // override should not apply to default
  type = catsxp_shields::GetFingerprintingControlType(map, GURL());
  EXPECT_EQ(ControlType::DEFAULT, type);
}

TEST_F(CatsxpShieldsUtilTest, GetFingerprintingControlType_ManagedPref) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedDefaultCatsxpFingerprintingV2, base::Value(CONTENT_SETTING_ALLOW));
  EXPECT_EQ(ControlType::ALLOW,
            catsxp_shields::GetFingerprintingControlType(map, GURL()));
  EXPECT_EQ(ControlType::ALLOW, catsxp_shields::GetFingerprintingControlType(
                                    map, GURL("http://catsxp.com")));

  profile()->GetTestingPrefService()->SetManagedPref(
      kManagedDefaultCatsxpFingerprintingV2, base::Value(CONTENT_SETTING_ASK));
  EXPECT_EQ(ControlType::DEFAULT,
            catsxp_shields::GetFingerprintingControlType(map, GURL()));
  EXPECT_EQ(ControlType::DEFAULT, catsxp_shields::GetFingerprintingControlType(
                                      map, GURL("http://catsxp.com")));
}

/* HTTPS UPGRADE */
TEST_F(CatsxpShieldsUtilTest, GetHttpsUpgradeControlType_ManagedPref) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCatsxpHttpsUpgrade,
      base::Value(CONTENT_SETTING_ALLOW));
  EXPECT_EQ(ControlType::ALLOW,
            catsxp_shields::GetHttpsUpgradeControlType(map, GURL()));
  EXPECT_EQ(ControlType::ALLOW, catsxp_shields::GetHttpsUpgradeControlType(
                                    map, GURL("http://catsxp.com")));

  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCatsxpHttpsUpgrade,
      base::Value(CONTENT_SETTING_BLOCK));
  EXPECT_EQ(ControlType::BLOCK,
            catsxp_shields::GetHttpsUpgradeControlType(map, GURL()));
  EXPECT_EQ(ControlType::BLOCK, catsxp_shields::GetHttpsUpgradeControlType(
                                    map, GURL("http://catsxp.com")));

  profile()->GetTestingPrefService()->SetManagedPref(
      prefs::kManagedDefaultCatsxpHttpsUpgrade,
      base::Value(CONTENT_SETTING_ASK));
  EXPECT_EQ(ControlType::BLOCK_THIRD_PARTY,
            catsxp_shields::GetHttpsUpgradeControlType(map, GURL()));
  EXPECT_EQ(
      ControlType::BLOCK_THIRD_PARTY,
      catsxp_shields::GetHttpsUpgradeControlType(map, GURL("http://catsxp.com")));
}

/* NOSCRIPT CONTROL */
TEST_F(CatsxpShieldsUtilTest, SetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  // settings should be default
  auto setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  /* BLOCK */
  catsxp_shields::SetNoScriptControlType(map, ControlType::BLOCK, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  /* ALLOW */
  catsxp_shields::SetNoScriptControlType(map, ControlType::ALLOW, GURL());
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);

  // override should apply to all origins
  setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(CatsxpShieldsUtilTest, SetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  catsxp_shields::SetNoScriptControlType(map, ControlType::BLOCK,
                                        GURL("http://catsxp.com"));
  // setting should apply to origin
  auto setting = map->GetContentSetting(GURL("http://catsxp.com"), GURL(),
                                        ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should also apply to different scheme
  setting = map->GetContentSetting(GURL("https://catsxp.com"), GURL(),
                                   ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_BLOCK, setting);

  // setting should not apply to default
  setting =
      map->GetContentSetting(GURL(), GURL(), ContentSettingsType::JAVASCRIPT);
  EXPECT_EQ(CONTENT_SETTING_ALLOW, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetNoScriptControlType_Default) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  /* ALLOW */
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_ALLOW);
  setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
}

TEST_F(CatsxpShieldsUtilTest, GetNoScriptControlType_ForOrigin) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());

  auto setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* BLOCK */
  // set override to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://catsxp.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT,
      CONTENT_SETTING_BLOCK);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("http://catsxp.com/*"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // https in unchanged
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);
  // default is unchanged
  setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::ALLOW, setting);

  /* ALLOW */
  // change default to block
  map->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::JAVASCRIPT, CONTENT_SETTING_BLOCK);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);

  map->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://catsxp.com/*"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::JAVASCRIPT,
      CONTENT_SETTING_ALLOW);
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("http://catsxp.com"));
  EXPECT_EQ(ControlType::ALLOW, setting);

  // https in unchanged
  setting =
      catsxp_shields::GetNoScriptControlType(map, GURL("https://catsxp.com"));
  EXPECT_EQ(ControlType::BLOCK, setting);
  // default is unchanged
  setting = catsxp_shields::GetNoScriptControlType(map, GURL());
  EXPECT_EQ(ControlType::BLOCK, setting);
}

// Should not do domain blocking if domain blocking feature is disabled
TEST_F(CatsxpShieldsUtilDomainBlockFeatureTest, GetDomainBlockingType) {
  ExpectDomainBlockingType(GURL("https://catsxp.com"),
                           DomainBlockingType::kNone);
}

// Should not do domain blocking if Catsxp Shields is down
TEST_F(CatsxpShieldsUtilTest, GetDomainBlockingType_ShieldsDown) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  GURL url = GURL("https://catsxp.com");
  catsxp_shields::SetCatsxpShieldsEnabled(map, false, url);
  ExpectDomainBlockingType(url, DomainBlockingType::kNone);
}

// Should not do domain blocking on non-HTTP(S) URLs
TEST_F(CatsxpShieldsUtilTest, GetDomainBlockingType_IsNotHttpHttps) {
  ExpectDomainBlockingType(GURL("chrome://preferences"),
                           DomainBlockingType::kNone);
  ExpectDomainBlockingType(GURL("about:blank"), DomainBlockingType::kNone);
}

// Should not do domain blocking unless ad blocking is "aggressive"
TEST_F(CatsxpShieldsUtilTest, GetDomainBlockingType_ControlTypes) {
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile());
  const GURL url = GURL("https://catsxp.com");

  const struct TestCase {
    ControlType ad_control_type;
    ControlType cosmetic_filtering_control_type;
    DomainBlockingType expected_blocking_type;
  } kTestCases[] = {
      {ControlType::ALLOW, ControlType::ALLOW, DomainBlockingType::kNone},
      {ControlType::ALLOW, ControlType::BLOCK_THIRD_PARTY,
       DomainBlockingType::kNone},
      {ControlType::ALLOW, ControlType::BLOCK, DomainBlockingType::kNone},
      {ControlType::BLOCK, ControlType::ALLOW, DomainBlockingType::kNone},
      {ControlType::BLOCK, ControlType::BLOCK_THIRD_PARTY,
       DomainBlockingType::k1PES},
      {ControlType::BLOCK, ControlType::BLOCK, DomainBlockingType::kAggressive},
  };

  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(testing::Message()
                 << static_cast<int>(test_case.ad_control_type)
                 << static_cast<int>(test_case.cosmetic_filtering_control_type)
                 << static_cast<int>(test_case.expected_blocking_type));
    catsxp_shields::SetAdControlType(map, test_case.ad_control_type, url);
    catsxp_shields::SetCosmeticFilteringControlType(
        map, test_case.cosmetic_filtering_control_type, url);
    ExpectDomainBlockingType(url, test_case.expected_blocking_type);
  }
}

// Should do 1PES domain blocking if domain blocking feature is enabled.
TEST_F(CatsxpShieldsUtilTest, GetDomainBlockingType) {
  ExpectDomainBlockingType(GURL("https://catsxp.com"),
                           DomainBlockingType::k1PES);
}
