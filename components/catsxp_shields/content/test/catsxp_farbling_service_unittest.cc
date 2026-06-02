/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/catsxp_farbling_service.h"

#include <array>
#include <memory>
#include <tuple>

#include "base/test/task_environment.h"
#include "base/token.h"
#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_utils.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

class CatsxpFarblingServiceTest : public testing::Test {
 public:
  CatsxpFarblingServiceTest() = default;
  CatsxpFarblingServiceTest(const CatsxpFarblingServiceTest&) = delete;
  CatsxpFarblingServiceTest& operator=(const CatsxpFarblingServiceTest&) = delete;
  ~CatsxpFarblingServiceTest() override = default;

  void SetUp() override {
    HostContentSettingsMap::RegisterProfilePrefs(prefs_.registry());
    settings_map_ = new HostContentSettingsMap(
        &prefs_, false /* is_off_the_record */, false /* store_last_modified */,
        false /* restore_session */, false /* should_record_metrics */);
    farbling_service_ =
        std::make_unique<catsxp::CatsxpFarblingService>(settings_map_.get());
  }

  void TearDown() override { settings_map_->ShutdownOnUIThread(); }

  catsxp::CatsxpFarblingService* farbling_service() {
    return farbling_service_.get();
  }

 protected:
  base::test::TaskEnvironment task_environment_;
  sync_preferences::TestingPrefServiceSyncable prefs_;
  scoped_refptr<HostContentSettingsMap> settings_map_;
  std::unique_ptr<catsxp::CatsxpFarblingService> farbling_service_;
};

TEST_F(CatsxpFarblingServiceTest, PRNGKnownValues) {
  const std::array<std::tuple<GURL, uint64_t>, 2> test_cases = {
      std::make_tuple<>(GURL("http://a.com"), 10450951993123491723UL),
      std::make_tuple<>(GURL("http://b.com"), 2581208260237394178UL),
  };
  for (const auto& c : test_cases) {
    catsxp::FarblingPRNG prng;
    ASSERT_TRUE(farbling_service()->MakePseudoRandomGeneratorForURL(
        std::get<0>(c), {}, &prng));
    EXPECT_EQ(prng(), std::get<1>(c));
  }
}

TEST_F(CatsxpFarblingServiceTest, PRNGKnownValuesDifferentSeeds) {
  const std::array<std::tuple<GURL, uint64_t>, 2> test_cases = {
      std::make_tuple<>(GURL("http://a.com"), 10450951993123491723UL),
      std::make_tuple<>(GURL("http://b.com"), 2581208260237394178UL),
  };
  for (const auto& c : test_cases) {
    catsxp::FarblingPRNG prng;
    ASSERT_TRUE(farbling_service()->MakePseudoRandomGeneratorForURL(
        std::get<0>(c), {}, &prng));
    EXPECT_EQ(prng(), std::get<1>(c));
  }
}

TEST_F(CatsxpFarblingServiceTest, InvalidDomains) {
  const std::array<GURL, 8> test_cases = {
      GURL("about:blank"),
      GURL("catsxp://settings"),
      GURL("chrome://version"),
      GURL("file:///etc/passwd"),
      GURL("javascript:alert(1)"),
      GURL("data:text/plain;base64,"),
      GURL(""),
  };
  for (const auto& url : test_cases) {
    catsxp::FarblingPRNG prng;
    EXPECT_FALSE(
        farbling_service()->MakePseudoRandomGeneratorForURL(url, {}, &prng));
    EXPECT_FALSE(
        farbling_service()->MakePseudoRandomGeneratorForURL(url, {}, &prng));
  }
}

TEST_F(CatsxpFarblingServiceTest, ShieldsDown) {
  const GURL url("http://a.com");
  catsxp_shields::SetCatsxpShieldsEnabled(settings_map_.get(), false, url);
  catsxp::FarblingPRNG prng;
  EXPECT_FALSE(
      farbling_service()->MakePseudoRandomGeneratorForURL(url, {}, &prng));
}

TEST_F(CatsxpFarblingServiceTest, FingerprintingAllowed) {
  const GURL url("http://a.com");
  catsxp_shields::SetFingerprintingControlType(
      settings_map_.get(), catsxp_shields::ControlType::ALLOW, url);
  catsxp::FarblingPRNG prng;
  EXPECT_FALSE(
      farbling_service()->MakePseudoRandomGeneratorForURL(url, {}, &prng));
}
