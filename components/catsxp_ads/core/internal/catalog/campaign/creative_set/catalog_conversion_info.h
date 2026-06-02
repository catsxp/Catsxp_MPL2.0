/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_CONVERSION_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_CONVERSION_INFO_H_

#include <string>
#include <vector>

#include "base/time/time.h"

namespace catsxp_ads {

struct CatalogConversionInfo final {
  CatalogConversionInfo();

  CatalogConversionInfo(const CatalogConversionInfo&);
  CatalogConversionInfo& operator=(const CatalogConversionInfo&);

  CatalogConversionInfo(CatalogConversionInfo&&) noexcept;
  CatalogConversionInfo& operator=(CatalogConversionInfo&&) noexcept;

  ~CatalogConversionInfo();

  bool operator==(const CatalogConversionInfo&) const = default;

  std::string creative_set_id;
  std::string url_pattern;
  base::TimeDelta observation_window;
  base::Time expire_at;
};

using CatalogConversionList = std::vector<CatalogConversionInfo>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CATALOG_CONVERSION_INFO_H_
