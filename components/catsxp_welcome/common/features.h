/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_WELCOME_COMMON_FEATURES_H_
#define CATSXP_COMPONENTS_CATSXP_WELCOME_COMMON_FEATURES_H_

#include "base/feature_list.h"

namespace catsxp_welcome {
namespace features {

// If enabled, this will show the Catsxp Rewards card in onboarding
BASE_DECLARE_FEATURE(kShowRewardsCard);

}  // namespace features
}  // namespace catsxp_welcome

#endif  // CATSXP_COMPONENTS_CATSXP_WELCOME_COMMON_FEATURES_H_
