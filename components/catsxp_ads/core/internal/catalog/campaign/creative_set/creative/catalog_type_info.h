/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_TYPE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_TYPE_INFO_H_

#include <string>

namespace catsxp_ads {

struct CatalogTypeInfo final {
  CatalogTypeInfo();

  CatalogTypeInfo(const CatalogTypeInfo&);
  CatalogTypeInfo& operator=(const CatalogTypeInfo&);

  CatalogTypeInfo(CatalogTypeInfo&&) noexcept;
  CatalogTypeInfo& operator=(CatalogTypeInfo&&) noexcept;

  ~CatalogTypeInfo();

  bool operator==(const CatalogTypeInfo&) const = default;

  std::string code;
  std::string name;
  std::string platform;
  int version = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CAMPAIGN_CREATIVE_SET_CREATIVE_CATALOG_TYPE_INFO_H_
