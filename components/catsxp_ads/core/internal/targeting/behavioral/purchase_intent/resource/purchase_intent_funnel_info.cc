/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_funnel_info.h"

#include <utility>

namespace catsxp_ads {

PurchaseIntentFunnelInfo::PurchaseIntentFunnelInfo() = default;

PurchaseIntentFunnelInfo::PurchaseIntentFunnelInfo(SegmentList segments,
                                                   int weight)
    : segments(std::move(segments)), weight(weight) {}

PurchaseIntentFunnelInfo::PurchaseIntentFunnelInfo(
    const PurchaseIntentFunnelInfo& other) = default;

PurchaseIntentFunnelInfo& PurchaseIntentFunnelInfo::operator=(
    const PurchaseIntentFunnelInfo& other) = default;

PurchaseIntentFunnelInfo::PurchaseIntentFunnelInfo(
    PurchaseIntentFunnelInfo&& other) noexcept = default;

PurchaseIntentFunnelInfo& PurchaseIntentFunnelInfo::operator=(
    PurchaseIntentFunnelInfo&& other) noexcept = default;

PurchaseIntentFunnelInfo::~PurchaseIntentFunnelInfo() = default;

}  // namespace catsxp_ads
