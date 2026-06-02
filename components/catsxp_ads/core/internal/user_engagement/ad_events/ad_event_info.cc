/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

namespace catsxp_ads {

AdEventInfo::AdEventInfo() = default;

AdEventInfo::AdEventInfo(const AdEventInfo& other) = default;

AdEventInfo& AdEventInfo::operator=(const AdEventInfo& other) = default;

AdEventInfo::AdEventInfo(AdEventInfo&& other) noexcept = default;

AdEventInfo& AdEventInfo::operator=(AdEventInfo&& other) noexcept = default;

AdEventInfo::~AdEventInfo() = default;

bool AdEventInfo::IsValid() const {
  return type != mojom::AdType::kUndefined &&
         confirmation_type != mojom::ConfirmationType::kUndefined &&
         !placement_id.empty() && !creative_instance_id.empty() &&
         !creative_set_id.empty() && !campaign_id.empty() &&
         target_url.is_valid() && created_at;
}

}  // namespace catsxp_ads
