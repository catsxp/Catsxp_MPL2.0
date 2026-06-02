/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/catalog/campaign/creative_set/catalog_conversion_info.h"

namespace catsxp_ads {

CatalogConversionInfo::CatalogConversionInfo() = default;

CatalogConversionInfo::CatalogConversionInfo(
    const CatalogConversionInfo& other) = default;

CatalogConversionInfo& CatalogConversionInfo::operator=(
    const CatalogConversionInfo& other) = default;

CatalogConversionInfo::CatalogConversionInfo(
    CatalogConversionInfo&& other) noexcept = default;

CatalogConversionInfo& CatalogConversionInfo::operator=(
    CatalogConversionInfo&& other) noexcept = default;

CatalogConversionInfo::~CatalogConversionInfo() = default;

}  // namespace catsxp_ads
