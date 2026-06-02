/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_util.h"

#include <optional>

#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/common/search_engine/search_engine_info.h"
#include "third_party/re2/src/re2/re2.h"
#include "url/gurl.h"

namespace catsxp_ads {

namespace {

std::optional<SearchEngineInfo> FindSearchEngine(const GURL& url) {
  if (!url.is_valid()) {
    return std::nullopt;
  }

  const GURL url_with_empty_path = url.GetWithEmptyPath();

  for (const auto& search_engine : GetSearchEngines()) {
    if (RE2::FullMatch(url_with_empty_path.spec(), search_engine.url_pattern) ||
        RE2::FullMatch(url.spec(), search_engine.url_pattern)) {
      return search_engine;
    }
  }

  return std::nullopt;
}

}  // namespace

bool IsSearchEngine(const GURL& url) {
  return !!FindSearchEngine(url);
}

}  // namespace catsxp_ads
