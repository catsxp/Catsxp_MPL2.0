/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

namespace catsxp_ads {

BASE_FEATURE(kPurchaseIntentFeature,
             "PurchaseIntent",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace catsxp_ads
