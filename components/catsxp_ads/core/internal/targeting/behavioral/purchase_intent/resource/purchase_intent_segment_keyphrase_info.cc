/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_segment_keyphrase_info.h"

#include <utility>

namespace catsxp_ads {

PurchaseIntentSegmentKeyphraseInfo::PurchaseIntentSegmentKeyphraseInfo() =
    default;

PurchaseIntentSegmentKeyphraseInfo::PurchaseIntentSegmentKeyphraseInfo(
    SegmentList segments,
    KeywordList keywords)
    : segments(std::move(segments)), keywords(std::move(keywords)) {}

PurchaseIntentSegmentKeyphraseInfo::PurchaseIntentSegmentKeyphraseInfo(
    PurchaseIntentSegmentKeyphraseInfo&& other) noexcept = default;

PurchaseIntentSegmentKeyphraseInfo&
PurchaseIntentSegmentKeyphraseInfo::operator=(
    PurchaseIntentSegmentKeyphraseInfo&& other) noexcept = default;

PurchaseIntentSegmentKeyphraseInfo::~PurchaseIntentSegmentKeyphraseInfo() =
    default;

}  // namespace catsxp_ads
