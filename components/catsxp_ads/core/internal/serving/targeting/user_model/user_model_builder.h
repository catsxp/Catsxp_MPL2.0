/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_BUILDER_H_

#include "base/functional/callback.h"

namespace catsxp_ads {

struct UserModelInfo;

using BuildUserModelCallback = base::OnceCallback<void(UserModelInfo)>;

void BuildUserModel(BuildUserModelCallback callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_BUILDER_H_
