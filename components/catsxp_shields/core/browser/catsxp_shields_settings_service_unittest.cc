/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_settings_service.h"

#include "base/test/scoped_feature_list.h"
#include "base/test/task_environment.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_p3a.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "catsxp/components/catsxp_shields/core/common/features.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

using catsxp_shields::mojom::AdBlockMode;
using catsxp_shields::mojom::AutoShredMode;
using catsxp_shields::mojom::FingerprintMode;

class CatsxpShieldsSettingsServiceTest : public testing::Test {
 public:
  CatsxpShieldsSettingsServiceTest() {}
  ~CatsxpShieldsSettingsServiceTest() override = default;

  void SetUp() override {
    HostContentSettingsMap::RegisterProfilePrefs(profile_prefs_.registry());
    catsxp_shields::RegisterShieldsP3AProfilePrefs(profile_prefs_.registry());
    catsxp_shields::RegisterShieldsP3ALocalPrefs(local_state_.registry());
    host_content_settings_map_ = new HostContentSettingsMap(
        &profile_prefs_, false /* is_off_the_record */,
        false /* store_last_modified */, false /* restore_session */,
        false /* should_record_metrics */);
    catsxp_shields_settings_ =
        std::make_unique<catsxp_shields::CatsxpShieldsSettingsService>(
            *GetHostContentSettingsMap(), GetLocalState(), &profile_prefs_);
  }

  void TearDown() override { host_content_settings_map_->ShutdownOnUIThread(); }

  TestingPrefServiceSimple* GetLocalState() { return &local_state_; }
  HostContentSettingsMap* GetHostContentSettingsMap() {
    return host_content_settings_map_.get();
  }

  const GURL kTestUrl{"https://catsxp.com"};

  catsxp_shields::CatsxpShieldsSettingsService* catsxp_shields_settings() {
    return catsxp_shields_settings_.get();
  }

  base::Value AutoShredDictFrom(AutoShredMode mode) {
    base::Value dict(base::Value::Type::DICT);
    dict.GetDict().Set(catsxp_shields::AutoShredSetting::kName,
                       static_cast<int>(mode));
    return dict;
  }

 private:
  base::test::TaskEnvironment task_environment_;
  TestingPrefServiceSimple local_state_;
  sync_preferences::TestingPrefServiceSyncable profile_prefs_;
  scoped_refptr<HostContentSettingsMap> host_content_settings_map_;
  std::unique_ptr<catsxp_shields::CatsxpShieldsSettingsService>
      catsxp_shields_settings_;
};

TEST_F(CatsxpShieldsSettingsServiceTest, CatsxpShieldsEnabled) {
  // verify the initial values
  EXPECT_TRUE(catsxp_shields_settings()->GetCatsxpShieldsEnabled(kTestUrl));
  EXPECT_TRUE(catsxp_shields::GetCatsxpShieldsEnabled(GetHostContentSettingsMap(),
                                                    kTestUrl));

  catsxp_shields_settings()->SetCatsxpShieldsEnabled(false, kTestUrl);
  EXPECT_FALSE(catsxp_shields_settings()->GetCatsxpShieldsEnabled(kTestUrl));
  // verify underlying value GetCatsxpShieldsEnabled is updated
  EXPECT_FALSE(catsxp_shields::GetCatsxpShieldsEnabled(
      GetHostContentSettingsMap(), kTestUrl));

  // verify other urls unchanged
  EXPECT_TRUE(catsxp_shields_settings()->GetCatsxpShieldsEnabled(
      GURL("https://example.com")));
  EXPECT_TRUE(catsxp_shields::GetCatsxpShieldsEnabled(
      GetHostContentSettingsMap(), GURL("https://example.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest, AdBlockMode) {
  // verify the initial values
  EXPECT_EQ(catsxp_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::STANDARD);
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::BLOCK_THIRD_PARTY);

  catsxp_shields_settings()->SetAdBlockMode(AdBlockMode::AGGRESSIVE, kTestUrl);
  EXPECT_EQ(catsxp_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::BLOCK);

  catsxp_shields_settings()->SetAdBlockMode(AdBlockMode::ALLOW, kTestUrl);
  EXPECT_EQ(catsxp_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::ALLOW);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      catsxp_shields::ControlType::ALLOW);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::ALLOW);

  // verify other urls remain unchanged
  EXPECT_EQ(
      catsxp_shields_settings()->GetAdBlockMode(GURL("https://example.com")),
      AdBlockMode::STANDARD);
}

TEST_F(CatsxpShieldsSettingsServiceTest, DefaultAdBlockMode) {
  // explicitly set so we can verify this is unchanged by updating default
  catsxp_shields_settings()->SetAdBlockMode(AdBlockMode::STANDARD, kTestUrl);

  // verify the initial default values
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultAdBlockMode(),
            AdBlockMode::STANDARD);
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), GURL()),
      catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL()),
            catsxp_shields::ControlType::BLOCK_THIRD_PARTY);

  catsxp_shields_settings()->SetDefaultAdBlockMode(AdBlockMode::AGGRESSIVE);
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultAdBlockMode(),
            AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), GURL()),
      catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL()),
            catsxp_shields::ControlType::BLOCK);
  // verify defaults apply to all
  EXPECT_EQ(
      catsxp_shields_settings()->GetAdBlockMode(GURL("https://example.com")),
      AdBlockMode::AGGRESSIVE);
  // verify underlying AdControlType & CosmeticFilteringControlType is updated
  EXPECT_EQ(catsxp_shields::GetAdControlType(GetHostContentSettingsMap(),
                                            GURL("https://example.com")),
            catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), GURL("https://example.com")),
            catsxp_shields::ControlType::BLOCK);

  // verify explict set adblock mode is unchanged
  EXPECT_EQ(catsxp_shields_settings()->GetAdBlockMode(kTestUrl),
            AdBlockMode::STANDARD);
  // verify underlying AdControlType & CosmeticFilteringControlType is unchanged
  EXPECT_EQ(
      catsxp_shields::GetAdControlType(GetHostContentSettingsMap(), kTestUrl),
      catsxp_shields::ControlType::BLOCK);
  EXPECT_EQ(catsxp_shields::GetCosmeticFilteringControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::BLOCK_THIRD_PARTY);
}

TEST_F(CatsxpShieldsSettingsServiceTest, FingerprintMode) {
  // verify the initial values
  EXPECT_EQ(catsxp_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::DEFAULT);

  catsxp_shields_settings()->SetFingerprintMode(FingerprintMode::ALLOW_MODE,
                                               kTestUrl);
  EXPECT_EQ(catsxp_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::ALLOW_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::ALLOW);

  // iOS does not support FingerprintMode::STRICT_MODE
#if !BUILDFLAG(IS_IOS)
  // when kCatsxpShowStrictFingerprintingMode flag is disabled
  catsxp_shields_settings()->SetFingerprintMode(FingerprintMode::STRICT_MODE,
                                               kTestUrl);
  // verify it returns FingerprintMode::STANDARD_MODE
  EXPECT_EQ(catsxp_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::DEFAULT);

  // enable kCatsxpShowStrictFingerprintingMode flag
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeature(
      catsxp_shields::features::kCatsxpShowStrictFingerprintingMode);
  catsxp_shields_settings()->SetFingerprintMode(FingerprintMode::STRICT_MODE,
                                               kTestUrl);
  // verify it returns FingerprintMode::STRICT_MODE
  EXPECT_EQ(catsxp_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STRICT_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::BLOCK);
#endif

  // verify other urls remain unchanged
  EXPECT_EQ(
      catsxp_shields_settings()->GetFingerprintMode(GURL("https://example.com")),
      FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is unchanged
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL("https://example.com")),
            catsxp_shields::ControlType::DEFAULT);
}

TEST_F(CatsxpShieldsSettingsServiceTest, DefaultFingerprintMode) {
  // explicitly set so we can verify this is unchanged by updating default
  catsxp_shields_settings()->SetFingerprintMode(FingerprintMode::STANDARD_MODE,
                                               kTestUrl);

  // verify the initial default values
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultFingerprintMode(),
            FingerprintMode::STANDARD_MODE);
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL()),
            catsxp_shields::ControlType::DEFAULT);

  catsxp_shields_settings()->SetDefaultFingerprintMode(
      FingerprintMode::ALLOW_MODE);
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultFingerprintMode(),
            FingerprintMode::ALLOW_MODE);
  // verify underlying FingerprintingControlType is updated
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), GURL()),
            catsxp_shields::ControlType::ALLOW);

  EXPECT_EQ(
      catsxp_shields_settings()->GetFingerprintMode(GURL("https://example.com")),
      FingerprintMode::ALLOW_MODE);

  // verify explict set fingerprint mode is unchanged
  EXPECT_EQ(catsxp_shields_settings()->GetFingerprintMode(kTestUrl),
            FingerprintMode::STANDARD_MODE);
  // verify underlying FingerprintingControlType is unchanged
  EXPECT_EQ(catsxp_shields::GetFingerprintingControlType(
                GetHostContentSettingsMap(), kTestUrl),
            catsxp_shields::ControlType::DEFAULT);
}

TEST_F(CatsxpShieldsSettingsServiceTest, NoScriptsEnabled) {
  // verify the initial values
  EXPECT_FALSE(catsxp_shields_settings()->IsNoScriptEnabled(kTestUrl));
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            catsxp_shields::ControlType::ALLOW);

  catsxp_shields_settings()->SetNoScriptEnabled(true, kTestUrl);
  EXPECT_TRUE(catsxp_shields_settings()->IsNoScriptEnabled(kTestUrl));
  // verify underlying NoScriptControlType is updated
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            catsxp_shields::ControlType::BLOCK);

  // verify other urls remain unchanged
  EXPECT_FALSE(
      catsxp_shields_settings()->IsNoScriptEnabled(GURL("https://example.com")));
  // verify underlying NoScriptControlType is unchanged
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL("https://example.com")),
            catsxp_shields::ControlType::ALLOW);
}

TEST_F(CatsxpShieldsSettingsServiceTest, NoScriptsEnabledByDefault) {
  // explicitly set so we can verify this is unchanged by updating default
  catsxp_shields_settings()->SetNoScriptEnabled(false, kTestUrl);

  // verify the initial default values
  EXPECT_FALSE(catsxp_shields_settings()->IsNoScriptEnabledByDefault());
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL()),
            catsxp_shields::ControlType::ALLOW);

  catsxp_shields_settings()->SetNoScriptEnabledByDefault(true);
  EXPECT_TRUE(catsxp_shields_settings()->IsNoScriptEnabledByDefault());
  EXPECT_TRUE(
      catsxp_shields_settings()->IsNoScriptEnabled(GURL("https://example.com")));
  // verify underlying NoScriptControlType is updated
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  GURL()),
            catsxp_shields::ControlType::BLOCK);

  // verify explict set no script enabled setting is unchanged
  EXPECT_FALSE(catsxp_shields_settings()->IsNoScriptEnabled(kTestUrl));
  // verify underlying NoScriptControlType is unchanged
  EXPECT_EQ(catsxp_shields::GetNoScriptControlType(GetHostContentSettingsMap(),
                                                  kTestUrl),
            catsxp_shields::ControlType::ALLOW);
}

class CatsxpShieldsSettingsServiceShredFeatureTest
    : public CatsxpShieldsSettingsServiceTest {
 public:
  CatsxpShieldsSettingsServiceShredFeatureTest() {
    scoped_feature_list_.InitAndEnableFeature(
        catsxp_shields::features::kCatsxpShredFeature);
  }

 private:
  base::test::ScopedFeatureList scoped_feature_list_;
};

TEST_F(CatsxpShieldsSettingsServiceShredFeatureTest, AutoShredMode) {
  // verify the initial values
  EXPECT_EQ(catsxp_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));

  catsxp_shields_settings()->SetAutoShredMode(AutoShredMode::LAST_TAB_CLOSED,
                                             kTestUrl);
  EXPECT_EQ(catsxp_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::LAST_TAB_CLOSED);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::LAST_TAB_CLOSED));

  catsxp_shields_settings()->SetAutoShredMode(AutoShredMode::APP_EXIT, kTestUrl);
  EXPECT_EQ(catsxp_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::APP_EXIT);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::APP_EXIT));

  // verify other urls remain unchanged
  EXPECT_EQ(
      catsxp_shields_settings()->GetAutoShredMode(GURL("https://example.com")),
      AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL("https://example.com"), GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));
}

TEST_F(CatsxpShieldsSettingsServiceShredFeatureTest, DefaultAutoShredMode) {
  // explicitly set so we can verify this is unchanged by updating default
  catsxp_shields_settings()->SetAutoShredMode(AutoShredMode::NEVER, kTestUrl);

  // verify the initial default values
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultAutoShredMode(),
            AutoShredMode::NEVER);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));

  catsxp_shields_settings()->SetDefaultAutoShredMode(
      AutoShredMode::LAST_TAB_CLOSED);
  EXPECT_EQ(catsxp_shields_settings()->GetDefaultAutoShredMode(),
            AutoShredMode::LAST_TAB_CLOSED);
  EXPECT_EQ(
      catsxp_shields_settings()->GetAutoShredMode(GURL("https://example.com")),
      AutoShredMode::LAST_TAB_CLOSED);
  // verify underlying AutoShredMode is updated
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::LAST_TAB_CLOSED));

  // verify explict set auto shred mode unchanged
  EXPECT_EQ(catsxp_shields_settings()->GetAutoShredMode(kTestUrl),
            AutoShredMode::NEVER);
  // verify underlying AutoShredMode is unchanged
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                kTestUrl, GURL(),
                catsxp_shields::AutoShredSetting::kContentSettingsType),
            AutoShredDictFrom(AutoShredMode::NEVER));
}

#if !BUILDFLAG(IS_IOS)
TEST_F(CatsxpShieldsSettingsServiceTest, DefaultForgetFirstPartyStorage) {
  // verify the initial values
  EXPECT_EQ(catsxp_shields_settings()->GetForgetFirstPartyStorageEnabled(GURL()),
            false);
  EXPECT_EQ(
      catsxp_shields_settings()->GetForgetFirstPartyStorageEnabled(kTestUrl),
      false);
}

TEST_F(CatsxpShieldsSettingsServiceTest, DefaultForgetFirstPartyStorageEnabled) {
  // verify the initial default values
  EXPECT_EQ(catsxp_shields_settings()->GetForgetFirstPartyStorageEnabled(GURL()),
            false);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                GURL(), GURL(), ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_ALLOW);
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       SetForgetFirstPartyStorageEnabledUsesETLD) {
  const GURL test_url("https://catsxp.com");
  const GURL test_subdomain_url("https://www.catsxp.com");

  EXPECT_EQ(
      GetHostContentSettingsMap()->GetWebsiteSetting(
          test_url, GURL(), ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE),
      CONTENT_SETTING_ALLOW);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                test_subdomain_url, GURL(),
                ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_ALLOW);

  catsxp_shields_settings()->SetForgetFirstPartyStorageEnabled(
      true, test_subdomain_url);

  EXPECT_EQ(
      GetHostContentSettingsMap()->GetWebsiteSetting(
          test_url, GURL(), ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE),
      CONTENT_SETTING_BLOCK);
  EXPECT_EQ(GetHostContentSettingsMap()->GetWebsiteSetting(
                test_subdomain_url, GURL(),
                ContentSettingsType::CATSXP_REMEMBER_1P_STORAGE),
            CONTENT_SETTING_BLOCK);
}
#endif

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_NoSettings) {
  // With no shield settings, should return false
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_ExactDomainMatch) {
  // Tests exact domain matching
  const auto example_com_url = GURL("https://example.com");
  catsxp_shields_settings()->SetCatsxpShieldsEnabled(false, example_com_url);
  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_WildcardPattern) {
  // Set shields to BLOCK for wildcard pattern
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("[*.]example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_SubdomainPattern) {
  // Tests specific subdomain patterns
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("sub.example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_AllowSettingIgnored) {
  // Set shields to ALLOW (not BLOCK) - should be ignored
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_ALLOW);

  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_AllHostsPatternIgnored) {
  // Test whildcard hosts pattern
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::Wildcard(), ContentSettingsPattern::Wildcard(),
      ContentSettingsType::CATSXP_SHIELDS, CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_MultipleSettings) {
  // Set multiple settings - some matching, some not
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("test.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("other.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_ALLOW);

  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("[*.]example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://other.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://unrelated.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_DifferentSubdomains) {
  // Set shields to BLOCK for specific subdomain
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("mail.test.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  // Should match for test.com ephemeral domain
  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_PortsInPatterns) {
  // Test with patterns that include ports
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("example.com:8080"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com:8080")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_MixedSchemePatterns) {
  // Test with different scheme patterns
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("http://example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("https://test.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://test.com")));
}

TEST_F(CatsxpShieldsSettingsServiceTest,
       IsShieldsDisabledOnAnyHostMatchingDomainOf_DeepSubdomainHierarchy) {
  // Test with deeply nested subdomains
  GetHostContentSettingsMap()->SetContentSettingCustomScope(
      ContentSettingsPattern::FromString("a.b.c.d.example.com"),
      ContentSettingsPattern::Wildcard(), ContentSettingsType::CATSXP_SHIELDS,
      CONTENT_SETTING_BLOCK);

  EXPECT_TRUE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://example.com")));
  EXPECT_FALSE(
      catsxp_shields_settings()->IsShieldsDisabledOnAnyHostMatchingDomainOf(
          GURL("https://other.com")));
}
