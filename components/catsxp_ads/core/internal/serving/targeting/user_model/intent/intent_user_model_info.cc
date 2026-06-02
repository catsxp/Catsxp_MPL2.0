/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"

#include <utility>

namespace catsxp_ads {

IntentUserModelInfo::IntentUserModelInfo() = default;

IntentUserModelInfo::IntentUserModelInfo(SegmentList segments)
    : segments(std::move(segments)) {}

IntentUserModelInfo::IntentUserModelInfo(const IntentUserModelInfo& other) =
    default;

IntentUserModelInfo& IntentUserModelInfo::operator=(
    const IntentUserModelInfo& other) = default;

IntentUserModelInfo::IntentUserModelInfo(IntentUserModelInfo&& other) noexcept =
    default;

IntentUserModelInfo& IntentUserModelInfo::operator=(
    IntentUserModelInfo&& other) noexcept = default;

IntentUserModelInfo::~IntentUserModelInfo() = default;

}  // namespace catsxp_ads
