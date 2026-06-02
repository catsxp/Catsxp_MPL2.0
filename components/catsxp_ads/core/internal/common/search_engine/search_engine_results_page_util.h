/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_UTIL_H_

#include <optional>
#include <string>


class GURL;

namespace catsxp_ads {

bool IsSearchEngineResultsPage(const GURL& url);

std::optional<std::string> ExtractSearchTermQueryValue(const GURL& url);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_RESULTS_PAGE_UTIL_H_
