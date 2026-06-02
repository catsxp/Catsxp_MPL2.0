/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_

#include <optional>
#include <string>


namespace catsxp_ads::json::reader {

std::optional<std::string> ParseSubdivision(const std::string& json);

}  // namespace catsxp_ads::json::reader

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_JSON_READER_UTIL_H_
