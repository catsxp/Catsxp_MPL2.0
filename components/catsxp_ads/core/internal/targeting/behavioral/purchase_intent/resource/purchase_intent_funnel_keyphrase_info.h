/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_KEYPHRASE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_KEYPHRASE_INFO_H_

#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_types.h"

namespace catsxp_ads {

struct PurchaseIntentFunnelKeyphraseInfo final {
  PurchaseIntentFunnelKeyphraseInfo();

  PurchaseIntentFunnelKeyphraseInfo(const PurchaseIntentFunnelKeyphraseInfo&) =
      delete;
  PurchaseIntentFunnelKeyphraseInfo& operator=(
      const PurchaseIntentFunnelKeyphraseInfo&) = delete;

  PurchaseIntentFunnelKeyphraseInfo(
      PurchaseIntentFunnelKeyphraseInfo&& other) noexcept;
  PurchaseIntentFunnelKeyphraseInfo& operator=(
      PurchaseIntentFunnelKeyphraseInfo&& other) noexcept;

  ~PurchaseIntentFunnelKeyphraseInfo();

  KeywordList keywords;
  int weight = 0;
};

using PurchaseIntentFunnelKeyphraseList =
    std::vector<PurchaseIntentFunnelKeyphraseInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_KEYPHRASE_INFO_H_
