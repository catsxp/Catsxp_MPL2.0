/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTENT_INTENT_USER_MODEL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTENT_INTENT_USER_MODEL_INFO_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct IntentUserModelInfo final {
  IntentUserModelInfo();
  explicit IntentUserModelInfo(SegmentList segments);

  IntentUserModelInfo(const IntentUserModelInfo&);
  IntentUserModelInfo& operator=(const IntentUserModelInfo&);

  IntentUserModelInfo(IntentUserModelInfo&&) noexcept;
  IntentUserModelInfo& operator=(IntentUserModelInfo&&) noexcept;

  ~IntentUserModelInfo();

  bool operator==(const IntentUserModelInfo&) const = default;

  SegmentList segments;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_INTENT_INTENT_USER_MODEL_INFO_H_
