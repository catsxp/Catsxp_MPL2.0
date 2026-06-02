/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/commands/common/features.h"
#include "base/feature_list.h"

namespace commands::features {

// This feature enables a page a catsxp://commands which lists all available
// commands in Catsxp, and the shortcut for executing them. In future, this will
// allow configuring the shortcuts for various commands.
BASE_FEATURE(kCatsxpCommands, base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace commands::features
