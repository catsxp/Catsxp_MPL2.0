/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_sync/catsxp_sync_prefs.h"

#include <memory>

#include "base/base64.h"
#include "base/test/gtest_util.h"
#include "base/test/task_environment.h"
#include "build/build_config.h"
#include "components/prefs/testing_pref_service.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

#if BUILDFLAG(IS_ANDROID)
#include "components/sync/service/sync_prefs.h"
#endif

using testing::Eq;
using testing::IsEmpty;
using testing::Optional;

namespace catsxp_sync {

class CatsxpSyncPrefsTest : public testing::Test {
 protected:
  CatsxpSyncPrefsTest() {
    catsxp_sync::Prefs::RegisterProfilePrefs(pref_service_.registry());
    catsxp_sync_prefs_ = std::make_unique<catsxp_sync::Prefs>(&pref_service_);
#if BUILDFLAG(IS_ANDROID)
    syncer::SyncPrefs::RegisterProfilePrefs(pref_service_.registry());
    sync_prefs_ = std::make_unique<syncer::SyncPrefs>(&pref_service_);
#endif
  }

  catsxp_sync::Prefs* catsxp_sync_prefs() { return catsxp_sync_prefs_.get(); }

  PrefService* pref_service() { return &pref_service_; }

  base::test::SingleThreadTaskEnvironment task_environment_;
  TestingPrefServiceSimple pref_service_;
  std::unique_ptr<catsxp_sync::Prefs> catsxp_sync_prefs_;

#if BUILDFLAG(IS_ANDROID)
  std::unique_ptr<syncer::SyncPrefs> sync_prefs_;
#endif
};


using CatsxpSyncPrefsDeathTest = CatsxpSyncPrefsTest;

TEST_F(CatsxpSyncPrefsTest, LeaveChainDetailsMaxLenIOS) {
  catsxp_sync_prefs()->SetAddLeaveChainDetailBehaviourForTesting(
      catsxp_sync::Prefs::AddLeaveChainDetailBehaviour::kAdd);

  auto max_len = Prefs::GetLeaveChainDetailsMaxLenForTesting();

  std::string details("a");
  catsxp_sync_prefs()->AddLeaveChainDetail("", 0, details.c_str());
  details = catsxp_sync_prefs()->GetLeaveChainDetails();
  EXPECT_LE(details.size(), max_len);
  EXPECT_GE(details.size(), 1u);

  details.assign(max_len + 1, 'a');
  catsxp_sync_prefs()->AddLeaveChainDetail(__FILE__, __LINE__, details.c_str());
  details = catsxp_sync_prefs()->GetLeaveChainDetails();
  EXPECT_EQ(details.size(), max_len);
}

#if BUILDFLAG(IS_ANDROID)
// Upstream used to have SyncPrefs::SetPasswordSyncAllowed
// commit: 558ee269a65b72e02fd3e6f27cc0eed6836b9cae
// This ensures we can set passwords as a selected to sync type
TEST_F(CatsxpSyncPrefsTest, PasswordSyncAllowedExplicitValue) {
  using syncer::UserSelectableType;
  using syncer::UserSelectableTypeSet;

  // Make passwords explicitly enabled (no default value).
  sync_prefs_->SetSelectedTypesForSyncingUser(
      /*keep_everything_synced=*/false,
      /*registered_types=*/UserSelectableTypeSet::All(),
      /*selected_types=*/{UserSelectableType::kPasswords});

  EXPECT_TRUE(sync_prefs_->GetSelectedTypesForSyncingUser().Has(
      UserSelectableType::kPasswords));
}
#endif

}  // namespace catsxp_sync
