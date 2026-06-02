/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/containers/core/common/features.h"

namespace containers::features {

// Enable Container Tabs. Allows users to open websites in contained tabs,
// keeping different identities separate within the same browser profile.
BASE_FEATURE(kContainers, base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace containers::features
