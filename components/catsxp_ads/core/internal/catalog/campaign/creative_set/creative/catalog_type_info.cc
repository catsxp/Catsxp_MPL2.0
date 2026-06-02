/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/creative/catalog_type_info.h"

namespace catsxp_ads {

CatalogTypeInfo::CatalogTypeInfo() = default;

CatalogTypeInfo::CatalogTypeInfo(const CatalogTypeInfo& other) = default;

CatalogTypeInfo& CatalogTypeInfo::operator=(const CatalogTypeInfo& other) =
    default;

CatalogTypeInfo::CatalogTypeInfo(CatalogTypeInfo&& other) noexcept = default;

CatalogTypeInfo& CatalogTypeInfo::operator=(CatalogTypeInfo&& other) noexcept =
    default;

CatalogTypeInfo::~CatalogTypeInfo() = default;

}  // namespace catsxp_ads
