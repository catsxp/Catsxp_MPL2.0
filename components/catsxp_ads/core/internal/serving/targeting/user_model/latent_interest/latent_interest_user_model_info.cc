/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"

#include <utility>

namespace catsxp_ads {

LatentInterestUserModelInfo::LatentInterestUserModelInfo() = default;

LatentInterestUserModelInfo::LatentInterestUserModelInfo(SegmentList segments)
    : segments(std::move(segments)) {}

LatentInterestUserModelInfo::LatentInterestUserModelInfo(
    const LatentInterestUserModelInfo& other) = default;

LatentInterestUserModelInfo& LatentInterestUserModelInfo::operator=(
    const LatentInterestUserModelInfo& other) = default;

LatentInterestUserModelInfo::LatentInterestUserModelInfo(
    LatentInterestUserModelInfo&& other) noexcept = default;

LatentInterestUserModelInfo& LatentInterestUserModelInfo::operator=(
    LatentInterestUserModelInfo&& other) noexcept = default;

LatentInterestUserModelInfo::~LatentInterestUserModelInfo() = default;

}  // namespace catsxp_ads
