/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include <algorithm>

#include "base/check.h"
#include "base/files/scoped_temp_dir.h"
#include "base/path_service.h"
#include "catsxp/components/catsxp_shields/content/browser/ad_block_subscription_service_manager.h"
#include "catsxp/test/base/testing_catsxp_browser_process.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/chrome_sync_client.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "chrome/test/base/testing_profile_manager.h"
#include "components/prefs/testing_pref_service.h"
#include "components/search_engines/search_engines_pref_names.h"
#include "components/sync/test/test_sync_service.h"
#include "components/sync_preferences/pref_service_mock_factory.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

std::unique_ptr<Profile> CreateProfile(const base::FilePath& path) {
  SyncServiceFactory::GetInstance();

  sync_preferences::PrefServiceMockFactory factory;
  auto registry = base::MakeRefCounted<user_prefs::PrefRegistrySyncable>();
  std::unique_ptr<sync_preferences::PrefServiceSyncable> prefs(
      factory.CreateSyncable(registry.get()));
  RegisterUserProfilePrefs(registry.get());

  TestingProfile::Builder profile_builder;
  profile_builder.SetPrefService(std::move(prefs));
  profile_builder.SetPath(path);
  return profile_builder.Build();
}

void FakeAdBlockSubscriptionDownloadManagerGetter(
    base::OnceCallback<
        void(catsxp_shields::AdBlockSubscriptionDownloadManager*)>) {
  // no-op, subscription services are not currently used in unit tests
}

}  // namespace

namespace browser_sync {

class CatsxpSyncClientTest : public testing::Test {
 public:
  CatsxpSyncClientTest() = default;
  ~CatsxpSyncClientTest() override = default;

 protected:
  void SetUp() override {
    EXPECT_TRUE(temp_dir_.CreateUniqueTempDir());
    profile_ = CreateProfile(temp_dir_.GetPath());
    EXPECT_TRUE(profile_);

    SetupAdblockServiceForCatsxpBrowserProcess();
  }

  Profile* profile() { return profile_.get(); }

 private:
  void SetupAdblockServiceForCatsxpBrowserProcess();

  // Need this as a very first member to run tests in UI thread
  // When this is set, class should not install any other MessageLoops, like
  // base::test::ScopedTaskEnvironment
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<Profile> profile_;
  base::ScopedTempDir temp_dir_;
};

// We need this because otherwise we'll get crash on uninitialized
// ad_block_service_ at
//    component_factory_->CreateCommonDataTypeControllers() =>
//    CreateAdBlockSubscriptionDownloadClient() =>
//    g_catsxp_browser_process->ad_block_service()
void CatsxpSyncClientTest::SetupAdblockServiceForCatsxpBrowserProcess() {
  base::FilePath user_data_dir;
  DCHECK(base::PathService::Get(chrome::DIR_USER_DATA, &user_data_dir));
  auto adblock_service = std::make_unique<catsxp_shields::AdBlockService>(
      TestingBrowserProcess::GetGlobal()->GetTestingLocalState(), "en", nullptr,
      base::SingleThreadTaskRunner::GetCurrentDefault(),
      std::make_unique<catsxp_shields::AdBlockSubscriptionServiceManager>(
          TestingBrowserProcess::GetGlobal()->GetTestingLocalState(),
          base::SingleThreadTaskRunner::GetCurrentDefault(),
          base::BindOnce(&FakeAdBlockSubscriptionDownloadManagerGetter),
          user_data_dir));

  TestingCatsxpBrowserProcess::GetGlobal()->SetAdBlockService(
      std::move(adblock_service));
}

TEST_F(CatsxpSyncClientTest, CreateDataTypeControllersSearchEngines) {
  auto sync_client =
      std::make_unique<browser_sync::ChromeSyncClient>(profile());

  syncer::TestSyncService service;
  const syncer::DataTypeController::TypeVector controllers =
      sync_client->CreateDataTypeControllers(&service);

  EXPECT_TRUE(std::ranges::any_of(
      controllers,
      [](const std::unique_ptr<syncer::DataTypeController>& controller) {
        return controller->type() == syncer::SEARCH_ENGINES;
      }));
}

TEST_F(CatsxpSyncClientTest, PrefSyncedDefaultSearchProviderGUIDIsSyncable) {
  // This test supposed to be near
  // components/search_engines/template_url_service.cc
  // But we have it here because we have profile here and both these tests are
  // related by the final purpose
  const PrefService::Preference* pref =
      profile()->GetPrefs()->FindPreference(prefs::kDefaultSearchProviderGUID);
  EXPECT_TRUE(pref->registration_flags() &
              user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
}

}  // namespace browser_sync
