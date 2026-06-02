/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model_segment_predictor.h"

#include <cstddef>

#include "base/containers/adapters.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

namespace catsxp_ads {

namespace {
constexpr size_t kMaximumSegments = 3;
}  // namespace

SegmentList PredictPurchaseIntentSegments(
    const std::multimap<int, std::string>& segment_scores) {
  if (segment_scores.empty()) {
    return {};
  }

  const int threshold = kPurchaseIntentThreshold.Get();

  SegmentList segments;
  segments.reserve(kMaximumSegments);

  for (const auto& [score, segment] : base::Reversed(segment_scores)) {
    if (score < threshold) {
      continue;
    }

    segments.push_back(segment);

    if (segments.size() == segment_scores.size() ||
        segments.size() >= kMaximumSegments) {
      break;
    }
  }

  return segments;
}

}  // namespace catsxp_ads
