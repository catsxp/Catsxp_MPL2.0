/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"

#include <utility>

namespace catsxp_ads {

InterestUserModelInfo::InterestUserModelInfo() = default;

InterestUserModelInfo::InterestUserModelInfo(SegmentList segments)
    : segments(std::move(segments)) {}

InterestUserModelInfo::InterestUserModelInfo(
    const InterestUserModelInfo& other) = default;

InterestUserModelInfo& InterestUserModelInfo::operator=(
    const InterestUserModelInfo& other) = default;

InterestUserModelInfo::InterestUserModelInfo(
    InterestUserModelInfo&& other) noexcept = default;

InterestUserModelInfo& InterestUserModelInfo::operator=(
    InterestUserModelInfo&& other) noexcept = default;

InterestUserModelInfo::~InterestUserModelInfo() = default;

}  // namespace catsxp_ads
