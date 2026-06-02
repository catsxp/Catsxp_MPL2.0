/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/logging_util_internal.h"

#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

void Log(const char* const file,
         int line,
         int verbose_level,
         const std::string& message) {
  if (GlobalState::HasInstance()) {
    GetAdsClient().Log(file, line, verbose_level, message);
  }
}

}  // namespace catsxp_ads
