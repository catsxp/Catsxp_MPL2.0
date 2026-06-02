/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_sync/features.h"

#include "base/feature_list.h"

namespace catsxp_sync::features {

BASE_FEATURE(kCatsxpSync, base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kCatsxpSyncDefaultPasswords,
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_sync::features
