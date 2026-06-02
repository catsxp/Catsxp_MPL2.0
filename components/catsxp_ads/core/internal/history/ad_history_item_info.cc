/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/history/ad_history_item_info.h"

namespace catsxp_ads {

AdHistoryItemInfo::AdHistoryItemInfo() = default;

AdHistoryItemInfo::AdHistoryItemInfo(const AdHistoryItemInfo& other) = default;

AdHistoryItemInfo& AdHistoryItemInfo::operator=(
    const AdHistoryItemInfo& other) = default;

AdHistoryItemInfo::AdHistoryItemInfo(AdHistoryItemInfo&& other) noexcept =
    default;

AdHistoryItemInfo& AdHistoryItemInfo::operator=(
    AdHistoryItemInfo&& other) noexcept = default;

AdHistoryItemInfo::~AdHistoryItemInfo() = default;

bool AdHistoryItemInfo::IsValid() const {
  return type != mojom::AdType::kUndefined &&
         confirmation_type != mojom::ConfirmationType::kUndefined &&
         !placement_id.empty() && !creative_instance_id.empty() &&
         !creative_set_id.empty() && !campaign_id.empty() &&
         !advertiser_id.empty() && !segment.empty() && !title.empty() &&
         !description.empty() && target_url.is_valid();
}

}  // namespace catsxp_ads
