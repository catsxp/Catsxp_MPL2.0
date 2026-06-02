/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_info.h"

namespace catsxp_ads {

CatalogInfo::CatalogInfo() = default;

CatalogInfo::CatalogInfo(const CatalogInfo& other) = default;

CatalogInfo& CatalogInfo::operator=(const CatalogInfo& other) = default;

CatalogInfo::CatalogInfo(CatalogInfo&& other) noexcept = default;

CatalogInfo& CatalogInfo::operator=(CatalogInfo&& other) noexcept = default;

CatalogInfo::~CatalogInfo() = default;

}  // namespace catsxp_ads
