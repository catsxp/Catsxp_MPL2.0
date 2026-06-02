/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/playlist/test/playlist_unittest_base.h"

#include <utility>

#include "catsxp/browser/playlist/playlist_service_factory.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "chrome/test/base/testing_browser_process.h"
#include "chrome/test/base/testing_profile.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"

namespace playlist {
PlaylistUnitTestBase::PlaylistUnitTestBase() = default;

PlaylistUnitTestBase::~PlaylistUnitTestBase() = default;

void PlaylistUnitTestBase::SetUp() {
  content::RenderViewHostTestHarness::SetUp();
}


std::unique_ptr<content::BrowserContext>
PlaylistUnitTestBase::CreateBrowserContext() {
  auto prefs = std::make_unique<sync_preferences::TestingPrefServiceSyncable>();
  RegisterUserProfilePrefs(prefs->registry());

  // `PlaylistServiceFactory` needs to be present in the dependency graph,
  // so that `PlaylistServiceFactory::RegisterProfilePrefs()` is triggered by
  // `DependencyManager::RegisterPrefsForServices()`
  PlaylistServiceFactory::GetInstance();

  return TestingProfile::Builder().SetPrefService(std::move(prefs)).Build();
}
}  // namespace playlist
