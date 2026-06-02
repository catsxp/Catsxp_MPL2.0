/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"

namespace catsxp_ads {

ConversionInfo::ConversionInfo() = default;

ConversionInfo::ConversionInfo(const ConversionInfo& other) = default;

ConversionInfo& ConversionInfo::operator=(const ConversionInfo& other) =
    default;

ConversionInfo::ConversionInfo(ConversionInfo&& other) noexcept = default;

ConversionInfo& ConversionInfo::operator=(ConversionInfo&& other) noexcept =
    default;

ConversionInfo::~ConversionInfo() = default;

bool ConversionInfo::IsValid() const {
  return ad_type != mojom::AdType::kUndefined &&
         !creative_instance_id.empty() && !creative_set_id.empty() &&
         !campaign_id.empty() && !advertiser_id.empty() &&
         action_type != ConversionActionType::kUndefined;
}

}  // namespace catsxp_ads
