/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_segments.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

namespace catsxp_ads {

void BuildIntentSegments(BuildSegmentsCallback callback) {
  SegmentList segments;

  if (base::FeatureList::IsEnabled(kPurchaseIntentFeature)) {
    segments = GetPurchaseIntentSegments();
  }

  std::move(callback).Run(segments);
}

}  // namespace catsxp_ads
