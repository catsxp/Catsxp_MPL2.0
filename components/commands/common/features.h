/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_COMMANDS_COMMON_FEATURES_H_
#define CATSXP_COMPONENTS_COMMANDS_COMMON_FEATURES_H_

#include "base/component_export.h"
#include "base/feature_list.h"

namespace commands::features {

COMPONENT_EXPORT(COMMANDS_COMMON) BASE_DECLARE_FEATURE(kCatsxpCommands);

}  // namespace commands::features

#endif  // CATSXP_COMPONENTS_COMMANDS_COMMON_FEATURES_H_
