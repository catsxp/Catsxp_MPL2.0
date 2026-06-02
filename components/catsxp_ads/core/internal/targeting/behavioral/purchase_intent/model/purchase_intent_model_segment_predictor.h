/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_SEGMENT_PREDICTOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_SEGMENT_PREDICTOR_H_

#include <map>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

SegmentList PredictPurchaseIntentSegments(
    const std::multimap<int, std::string>& segment_scores);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_MODEL_PURCHASE_INTENT_MODEL_SEGMENT_PREDICTOR_H_
