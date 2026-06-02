/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_JSON_READER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_JSON_READER_H_

#include <optional>
#include <string>

namespace catsxp_ads {

struct CatalogInfo;

namespace json::reader {

std::optional<CatalogInfo> ReadCatalog(const std::string& json);

}  // namespace json::reader

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_JSON_READER_H_
