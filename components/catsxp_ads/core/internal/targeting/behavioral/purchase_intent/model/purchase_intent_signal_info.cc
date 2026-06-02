/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_signal_info.h"

#include <utility>

namespace catsxp_ads {

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo() = default;

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo(base::Time at,
                                                   SegmentList segments,
                                                   int weight)
    : at(at), segments(std::move(segments)), weight(weight) {}

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo(
    const PurchaseIntentSignalInfo& other) = default;

PurchaseIntentSignalInfo& PurchaseIntentSignalInfo::operator=(
    const PurchaseIntentSignalInfo& other) = default;

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo(
    PurchaseIntentSignalInfo&& other) noexcept = default;

PurchaseIntentSignalInfo& PurchaseIntentSignalInfo::operator=(
    PurchaseIntentSignalInfo&& other) noexcept = default;

PurchaseIntentSignalInfo::~PurchaseIntentSignalInfo() = default;

}  // namespace catsxp_ads
