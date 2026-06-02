/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"

namespace catsxp_ads {

CreativeSetConversionInfo::CreativeSetConversionInfo() = default;

CreativeSetConversionInfo::CreativeSetConversionInfo(
    const CreativeSetConversionInfo& other) = default;

CreativeSetConversionInfo& CreativeSetConversionInfo::operator=(
    const CreativeSetConversionInfo& other) = default;

CreativeSetConversionInfo::CreativeSetConversionInfo(
    CreativeSetConversionInfo&& other) noexcept = default;

CreativeSetConversionInfo& CreativeSetConversionInfo::operator=(
    CreativeSetConversionInfo&& other) noexcept = default;

CreativeSetConversionInfo::~CreativeSetConversionInfo() = default;

bool CreativeSetConversionInfo::IsValid() const {
  return !id.empty() && !url_pattern.empty() &&
         !observation_window.is_negative() && expire_at;
}

}  // namespace catsxp_ads
