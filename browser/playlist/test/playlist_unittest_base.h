/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_
#define CATSXP_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_

#include <memory>

#include "base/test/scoped_feature_list.h"
#include "catsxp/components/playlist/core/common/features.h"
#include "components/prefs/testing_pref_service.h"
#include "content/public/test/test_renderer_host.h"

namespace content {
class BrowserContext;
}

namespace playlist {
class PlaylistUnitTestBase : public content::RenderViewHostTestHarness {
 public:
  PlaylistUnitTestBase();
  ~PlaylistUnitTestBase() override;

 protected:
  // testing::Test:
  void SetUp() override;

  // content::RenderViewHostTestHarness:
  std::unique_ptr<content::BrowserContext> CreateBrowserContext() override;

  base::test::ScopedFeatureList feature_list_{features::kPlaylist};
};
}  // namespace playlist

#endif  // CATSXP_BROWSER_PLAYLIST_TEST_PLAYLIST_UNITTEST_BASE_H_
