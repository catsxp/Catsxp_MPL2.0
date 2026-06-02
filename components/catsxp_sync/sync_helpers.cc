/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_sync/sync_helpers.h"

#include "base/command_line.h"
#include "catsxp/browser/catsxp_features_internal_names.h"

namespace catsxp_sync {

bool IsGoogleSync() {
  static const bool is_google_sync = []() {
    const base::CommandLine& command_line =
        *base::CommandLine::ForCurrentProcess();
    return command_line.HasSwitch(kCatsxpUsrGoogleSync);
  }();
  return is_google_sync;
}

}  // namespace catsxp_sync
