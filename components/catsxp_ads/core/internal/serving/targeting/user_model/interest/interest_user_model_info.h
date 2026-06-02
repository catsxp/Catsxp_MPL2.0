/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct InterestUserModelInfo final {
  InterestUserModelInfo();
  explicit InterestUserModelInfo(SegmentList segments);

  InterestUserModelInfo(const InterestUserModelInfo&);
  InterestUserModelInfo& operator=(const InterestUserModelInfo&);

  InterestUserModelInfo(InterestUserModelInfo&&) noexcept;
  InterestUserModelInfo& operator=(InterestUserModelInfo&&) noexcept;

  ~InterestUserModelInfo();

  bool operator==(const InterestUserModelInfo&) const = default;

  SegmentList segments;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTEREST_INTEREST_USER_MODEL_INFO_H_
