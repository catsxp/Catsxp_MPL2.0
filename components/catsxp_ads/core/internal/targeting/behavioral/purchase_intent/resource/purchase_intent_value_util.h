/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_VALUE_UTIL_H_

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_keyphrase_info.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_segment_keyphrase_info.h"

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

std::optional<int> ParseVersion(const base::DictValue& dict);

std::optional<SegmentList> ParseSegments(const base::DictValue& dict);

std::optional<PurchaseIntentSegmentKeyphraseList> ParseSegmentKeyphrases(
    const SegmentList& segments,
    const base::DictValue& dict);

std::optional<PurchaseIntentFunnelKeyphraseList> ParseFunnelKeyphrases(
    const base::DictValue& dict);

std::optional<PurchaseIntentFunnelSiteMap> ParseFunnelSites(
    const SegmentList& segments,
    const base::DictValue& dict);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_RESOURCE_PURCHASE_INTENT_VALUE_UTIL_H_
