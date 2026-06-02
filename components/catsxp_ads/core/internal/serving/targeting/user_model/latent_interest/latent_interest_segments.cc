/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_segments.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

void BuildLatentInterestSegments(BuildSegmentsCallback callback) {
  std::move(callback).Run(/*segments=*/{});
}

}  // namespace catsxp_ads
