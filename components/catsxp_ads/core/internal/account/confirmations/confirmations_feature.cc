/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kConfirmationsFeature,
             "Confirmations",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
