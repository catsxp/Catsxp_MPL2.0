/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource_info.h"

#include <utility>

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_value_util.h"

namespace catsxp_ads {

PurchaseIntentResourceInfo::PurchaseIntentResourceInfo() = default;

PurchaseIntentResourceInfo::PurchaseIntentResourceInfo(
    PurchaseIntentResourceInfo&& other) noexcept = default;

PurchaseIntentResourceInfo& PurchaseIntentResourceInfo::operator=(
    PurchaseIntentResourceInfo&& other) noexcept = default;

PurchaseIntentResourceInfo::~PurchaseIntentResourceInfo() = default;

// static
std::optional<PurchaseIntentResourceInfo>
PurchaseIntentResourceInfo::MaybeFromDict(const base::DictValue dict) {
  std::optional<int> version = ParseVersion(dict);
  if (!version) {
    return std::nullopt;
  }

  if (version != kPurchaseIntentResourceVersion.Get()) {
    return std::nullopt;
  }

  std::optional<SegmentList> segments = ParseSegments(dict);
  if (!segments) {
    return std::nullopt;
  }

  std::optional<PurchaseIntentSegmentKeyphraseList> segment_keyphrases =
      ParseSegmentKeyphrases(*segments, dict);
  if (!segment_keyphrases) {
    return std::nullopt;
  }

  std::optional<PurchaseIntentFunnelKeyphraseList> funnel_keyphrases =
      ParseFunnelKeyphrases(dict);
  if (!funnel_keyphrases) {
    return std::nullopt;
  }

  std::optional<PurchaseIntentFunnelSiteMap> funnel_sites =
      ParseFunnelSites(*segments, dict);
  if (!funnel_sites) {
    return std::nullopt;
  }

  PurchaseIntentResourceInfo purchase_intent;
  purchase_intent.version = version;
  purchase_intent.segment_keyphrases = std::move(*segment_keyphrases);
  purchase_intent.funnel_keyphrases = std::move(*funnel_keyphrases);
  purchase_intent.funnel_sites = *funnel_sites;

  return purchase_intent;
}

}  // namespace catsxp_ads
