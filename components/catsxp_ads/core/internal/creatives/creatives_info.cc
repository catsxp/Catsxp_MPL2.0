/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/creatives_info.h"

namespace catsxp_ads {

CreativesInfo::CreativesInfo() = default;

CreativesInfo::CreativesInfo(const CreativesInfo& other) = default;

CreativesInfo& CreativesInfo::operator=(const CreativesInfo& other) = default;

CreativesInfo::CreativesInfo(CreativesInfo&& other) noexcept = default;

CreativesInfo& CreativesInfo::operator=(CreativesInfo&& other) noexcept =
    default;

CreativesInfo::~CreativesInfo() = default;

}  // namespace catsxp_ads
