/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_

#include <map>
#include <string>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"

namespace catsxp_ads {

struct PurchaseIntentFunnelInfo final {
  PurchaseIntentFunnelInfo();
  PurchaseIntentFunnelInfo(SegmentList segments, int weight);

  PurchaseIntentFunnelInfo(const PurchaseIntentFunnelInfo&);
  PurchaseIntentFunnelInfo& operator=(const PurchaseIntentFunnelInfo&);

  PurchaseIntentFunnelInfo(PurchaseIntentFunnelInfo&&) noexcept;
  PurchaseIntentFunnelInfo& operator=(PurchaseIntentFunnelInfo&&) noexcept;

  ~PurchaseIntentFunnelInfo();

  bool operator==(const PurchaseIntentFunnelInfo&) const = default;

  SegmentList segments;
  int weight = 0;
};

using PurchaseIntentFunnelSiteMap =
    std::map</*url*/ std::string, PurchaseIntentFunnelInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_FUNNEL_INFO_H_
