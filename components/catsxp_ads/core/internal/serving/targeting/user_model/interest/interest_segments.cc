/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_segments.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/model/text_classification_model.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"

namespace catsxp_ads {

void BuildInterestSegments(BuildSegmentsCallback callback) {
  SegmentList segments;

  if (base::FeatureList::IsEnabled(kTextClassificationFeature)) {
    segments = GetTextClassificationSegments();
  }

  std::move(callback).Run(segments);
}

}  // namespace catsxp_ads
