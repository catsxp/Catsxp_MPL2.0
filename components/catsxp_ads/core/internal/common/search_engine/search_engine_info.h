/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_

#include <string>

namespace catsxp_ads {

struct SearchEngineInfo final {
  SearchEngineInfo(std::string url_pattern,
                   std::string result_page_url_pattern,
                   std::string search_term_query_key);

  std::string url_pattern;
  std::string result_page_url_pattern;
  std::string search_term_query_key;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_INFO_H_
