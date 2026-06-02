/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_LATENT_INTEREST_LATENT_INTEREST_USER_MODEL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_LATENT_INTEREST_LATENT_INTEREST_USER_MODEL_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct LatentInterestUserModelInfo final {
  LatentInterestUserModelInfo();
  explicit LatentInterestUserModelInfo(SegmentList segments);

  LatentInterestUserModelInfo(const LatentInterestUserModelInfo&);
  LatentInterestUserModelInfo& operator=(const LatentInterestUserModelInfo&);

  LatentInterestUserModelInfo(LatentInterestUserModelInfo&&) noexcept;
  LatentInterestUserModelInfo& operator=(
      LatentInterestUserModelInfo&&) noexcept;

  ~LatentInterestUserModelInfo();

  bool operator==(const LatentInterestUserModelInfo&) const = default;

  SegmentList segments;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_LATENT_INTEREST_LATENT_INTEREST_USER_MODEL_INFO_H_
