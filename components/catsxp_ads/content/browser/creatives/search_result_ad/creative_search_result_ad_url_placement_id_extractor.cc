/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/creative_search_result_ad_url_placement_id_extractor.h"

#include <optional>
#include <string_view>

#include "catsxp/components/catsxp_search/common/catsxp_search_utils.h"
#include "net/base/url_util.h"
#include "url/gurl.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kAllowedUrlPath = "/a/redirect";
constexpr std::string_view kPlacementIdQueryKey = "placement_id";

}  // namespace

std::optional<std::string> MaybeExtractCreativeAdPlacementIdFromUrl(
    const GURL& url) {
  if (!url.is_valid() || !url.SchemeIs(url::kHttpsScheme) ||
      url.path() != kAllowedUrlPath || !url.has_query() ||
      !catsxp_search::IsAllowedHost(url)) {
    return std::nullopt;
  }

  for (net::QueryIterator iter(url); !iter.IsAtEnd(); iter.Advance()) {
    if (iter.GetKey() == kPlacementIdQueryKey) {
      std::string placement_id{iter.GetValue()};
      if (placement_id.empty()) {
        return std::nullopt;
      }

      return placement_id;
    }
  }

  return std::nullopt;
}

}  // namespace catsxp_ads
