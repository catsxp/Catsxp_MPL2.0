/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_

#include <string>

#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-shared.h"
#include "url/gurl.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct AdInfo {
  AdInfo();

  AdInfo(const AdInfo&);
  AdInfo& operator=(const AdInfo&);

  AdInfo(AdInfo&&) noexcept;
  AdInfo& operator=(AdInfo&&) noexcept;

  ~AdInfo();

  bool operator==(const AdInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  mojom::AdType type = mojom::AdType::kUndefined;
  std::string placement_id;
  std::string creative_instance_id;
  std::string creative_set_id;
  std::string campaign_id;
  std::string advertiser_id;
  std::string segment;
  GURL target_url;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_AD_UNITS_AD_INFO_H_
