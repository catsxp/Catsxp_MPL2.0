/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_types.h"

namespace catsxp_ads {

struct PurchaseIntentSegmentKeyphraseInfo final {
  PurchaseIntentSegmentKeyphraseInfo();
  PurchaseIntentSegmentKeyphraseInfo(SegmentList segments,
                                     KeywordList keywords);

  PurchaseIntentSegmentKeyphraseInfo(
      const PurchaseIntentSegmentKeyphraseInfo&) = delete;
  PurchaseIntentSegmentKeyphraseInfo& operator=(
      const PurchaseIntentSegmentKeyphraseInfo&) = delete;

  PurchaseIntentSegmentKeyphraseInfo(
      PurchaseIntentSegmentKeyphraseInfo&&) noexcept;
  PurchaseIntentSegmentKeyphraseInfo& operator=(
      PurchaseIntentSegmentKeyphraseInfo&&) noexcept;

  ~PurchaseIntentSegmentKeyphraseInfo();

  SegmentList segments;
  KeywordList keywords;
};

using PurchaseIntentSegmentKeyphraseList =
    std::vector<PurchaseIntentSegmentKeyphraseInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_SEGMENT_KEYPHRASE_INFO_H_
