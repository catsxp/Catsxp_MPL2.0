/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_INFO_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"

namespace catsxp_ads {

struct ConversionInfo final {
  ConversionInfo();

  ConversionInfo(const ConversionInfo&);
  ConversionInfo& operator=(const ConversionInfo&);

  ConversionInfo(ConversionInfo&&) noexcept;
  ConversionInfo& operator=(ConversionInfo&&) noexcept;

  ~ConversionInfo();

  bool operator==(const ConversionInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  mojom::AdType ad_type = mojom::AdType::kUndefined;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  ConversionActionType action_type = ConversionActionType::kUndefined;
};

using ConversionList = std::vector<ConversionInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSION_CONVERSION_INFO_H_
