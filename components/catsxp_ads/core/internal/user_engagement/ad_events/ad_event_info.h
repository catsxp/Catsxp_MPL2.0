/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_

#include <optional>
#include <string>
#include <vector>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"
#include "url/gurl.h"

namespace catsxp_ads {

struct AdEventInfo final {
  AdEventInfo();

  AdEventInfo(const AdEventInfo&);
  AdEventInfo& operator=(const AdEventInfo&);

  AdEventInfo(AdEventInfo&&) noexcept;
  AdEventInfo& operator=(AdEventInfo&&) noexcept;

  ~AdEventInfo();

  bool operator==(const AdEventInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  mojom::AdType type = mojom::AdType::kUndefined;
  mojom::ConfirmationType confirmation_type =
      mojom::ConfirmationType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  GURL target_url;
  std::optional<base::Time> created_at;
};

using AdEventList = std::vector<AdEventInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_AD_EVENTS_AD_EVENT_INFO_H_
