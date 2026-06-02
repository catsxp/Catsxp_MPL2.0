/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_

#include <optional>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_keyphrase_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_segment_keyphrase_info.h"

namespace catsxp_ads {

struct PurchaseIntentResourceInfo final {
  PurchaseIntentResourceInfo();

  PurchaseIntentResourceInfo(const PurchaseIntentResourceInfo&) = delete;
  PurchaseIntentResourceInfo& operator=(const PurchaseIntentResourceInfo&) =
      delete;

  PurchaseIntentResourceInfo(PurchaseIntentResourceInfo&&) noexcept;
  PurchaseIntentResourceInfo& operator=(PurchaseIntentResourceInfo&&) noexcept;

  ~PurchaseIntentResourceInfo();

  static std::optional<PurchaseIntentResourceInfo> MaybeFromDict(
      base::DictValue dict);

  std::optional<int> version;
  PurchaseIntentSegmentKeyphraseList segment_keyphrases;
  PurchaseIntentFunnelKeyphraseList funnel_keyphrases;
  PurchaseIntentFunnelSiteMap funnel_sites;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_RESOURCE_INFO_H_
