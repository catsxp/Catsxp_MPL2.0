/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_info.h"

#include <utility>

namespace catsxp_ads {

SearchEngineInfo::SearchEngineInfo(std::string url_pattern,
                                   std::string result_page_url_pattern,
                                   std::string search_term_query_key)
    : url_pattern(std::move(url_pattern)),
      result_page_url_pattern(std::move(result_page_url_pattern)),
      search_term_query_key(std::move(search_term_query_key)) {}

}  // namespace catsxp_ads
