/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ad_units/ad_info.h"

namespace catsxp_ads {

AdInfo::AdInfo() = default;

AdInfo::AdInfo(const AdInfo& other) = default;

AdInfo& AdInfo::operator=(const AdInfo& other) = default;

AdInfo::AdInfo(AdInfo&& other) noexcept = default;

AdInfo& AdInfo::operator=(AdInfo&& other) noexcept = default;

AdInfo::~AdInfo() = default;

bool AdInfo::IsValid() const {
  return type != mojom::AdType::kUndefined && !placement_id.empty() &&
         !creative_instance_id.empty() && !creative_set_id.empty() &&
         !campaign_id.empty() && !advertiser_id.empty() && !segment.empty() &&
         target_url.is_valid();
}

}  // namespace catsxp_ads
