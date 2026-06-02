/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_INFO_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"
#include "url/gurl.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct AdHistoryItemInfo final {
  AdHistoryItemInfo();

  AdHistoryItemInfo(const AdHistoryItemInfo&);
  AdHistoryItemInfo& operator=(const AdHistoryItemInfo&);

  AdHistoryItemInfo(AdHistoryItemInfo&&) noexcept;
  AdHistoryItemInfo& operator=(AdHistoryItemInfo&&) noexcept;

  ~AdHistoryItemInfo();

  bool operator==(const AdHistoryItemInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  base::Time created_at;
  mojom::AdType type = mojom::AdType::kUndefined;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  std::string title;
  std::string description;
  GURL target_url;
};

using AdHistoryList = std::vector<AdHistoryItemInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_INFO_H_
