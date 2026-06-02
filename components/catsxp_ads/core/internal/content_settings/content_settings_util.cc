/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/content_settings/content_settings_util.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"

namespace catsxp_ads {

bool IsJavaScriptAllowed() {
  return GlobalState::GetInstance()->ContentSettings().allow_javascript;
}

}  // namespace catsxp_ads
