/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_SERVICE_BROWSERTEST_H_
#define CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_SERVICE_BROWSERTEST_H_

#include <memory>
#include <string>
#include <vector>

#include "base/files/scoped_temp_dir.h"
#include "base/task/sequenced_task_runner.h"
#include "base/test/metrics/histogram_tester.h"
#include "catsxp/components/catsxp_shields/content/test/test_filters_provider.h"
#include "chrome/test/base/platform_browser_test.h"
#include "content/public/test/content_mock_cert_verifier.h"

class HostContentSettingsMap;

namespace catsxp_shields {
class AdBlockBrowserTestHelper;
class AdBlockComponentServiceManager;
class AdBlockService;
class FilterListCatalogEntry;
}  // namespace catsxp_shields

class Profile;

class AdBlockServiceTest : public PlatformBrowserTest {
 public:
  AdBlockServiceTest();
  ~AdBlockServiceTest() override;

  // ExtensionBrowserTest overrides
  void SetUpCommandLine(base::CommandLine* command_line) override;
  void SetUpInProcessBrowserTestFixture() override;
  void SetUpOnMainThread() override;
  void PreRunTestOnMainThread() override;
  void TearDownOnMainThread() override;
  void TearDownInProcessBrowserTestFixture() override;

 protected:
  content::ContentMockCertVerifier mock_cert_verifier_;

  PrefService* local_state();
  HostContentSettingsMap* content_settings();
  catsxp_shields::AdBlockComponentServiceManager* component_service_manager();
  void AddNewRules(const std::string& rules,
                   uint8_t permission_mask = 0,
                   bool first_party_protections = false);
  void UpdateAdBlockResources(const std::string& resources);
  void UpdateAdBlockInstanceWithRules(const std::string& rules);
  void EnableDeveloperMode(bool enabled);
  void UpdateCustomAdBlockInstanceWithRules(const std::string& rules);
  void AssertTagExists(const std::string& tag, bool expected_exists) const;
  void InitEmbeddedTestServer();
  base::FilePath GetTestDataDir();
  void NavigateToURL(const GURL& url);
  void SetDefaultComponentIdAndBase64PublicKeyForTest();
  void SetRegionalComponentIdAndBase64PublicKeyForTest();
  void InstallComponent(
      const catsxp_shields::FilterListCatalogEntry& catalog_entry);
  void InstallDefaultAdBlockComponent();
  void InstallRegionalAdBlockComponent(const std::string& uuid,
                                       bool enable_list = true);
  void SetSubscriptionIntervals();
  void ShieldsDown(const GURL& url);
  void DisableAggressiveMode();
  void LoadDAT(base::FilePath path);
  void EnableRedirectUrlParsing();
  Profile* profile();
  content::WebContents* web_contents();
  base::FilePath MakeFileInTempDir(const std::string& name,
                                   const std::string& contents);
  base::FilePath MakeTestDataCopy(const base::FilePath& source_location);

  std::unique_ptr<catsxp_shields::AdBlockBrowserTestHelper>
      ad_block_test_helper_;

  std::vector<std::unique_ptr<catsxp_shields::TestFiltersProvider>>
      source_providers_;

  std::vector<std::unique_ptr<base::ScopedTempDir>> temp_dirs_;

  net::EmbeddedTestServer dynamic_server_;
  net::EmbeddedTestServer https_server_;

  const base::HistogramTester histogram_tester_;
};

#endif  // CATSXP_BROWSER_CATSXP_SHIELDS_AD_BLOCK_SERVICE_BROWSERTEST_H_
