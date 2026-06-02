/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/media_permission_rule.h"

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager.h"

namespace catsxp_ads {

bool HasMediaPermission() {
  if (!kShouldOnlyServeAdsIfMediaIsNotPlaying.Get()) {
    return true;
  }

  std::optional<TabInfo> tab = TabManager::GetInstance().MaybeGetVisible();
  if (!tab) {
    return true;
  }

  if (!TabManager::GetInstance().IsPlayingMedia(tab->id)) {
    return true;
  }

  BLOG(2, "Media is playing");
  return false;
}

}  // namespace catsxp_ads
