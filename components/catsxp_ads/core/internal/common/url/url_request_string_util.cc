
/* Copyright (c) 2020 The Catsxp Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/url_request_string_util.h"

#include <algorithm>
#include <sstream>
#include <string_view>
#include <vector>

#include "base/containers/fixed_flat_set.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr auto kAllowedHeaders = base::MakeFixedFlatSet<std::string_view>(
    {"accept", "content-type", "digest", "signature"});

bool ShouldAllowHeader(const std::string& header) {
  return std::ranges::any_of(kAllowedHeaders,
                             [&header](std::string_view allowed_header) {
                               return header.starts_with(allowed_header);
                             });
}

std::string HeadersToString(const std::vector<std::string>& headers,
                            const size_t indent = 4) {
  std::vector<std::string> formatted_headers;

  const std::string spaces(indent, ' ');

  for (const auto& header : headers) {
    if (ShouldAllowHeader(header)) {
      formatted_headers.push_back(spaces + header);
    }
  }

  return base::JoinString(formatted_headers, "\n");
}

}  // namespace

std::string UrlRequestToString(
    const mojom::UrlRequestInfoPtr& mojom_url_request) {
  std::string log = "URL Request:\n";

  log += base::ReplaceStringPlaceholders(
      "  URL: $1\n", {mojom_url_request->url.spec()}, nullptr);

  if (!mojom_url_request->content.empty()) {
    log += base::ReplaceStringPlaceholders(
        "  Content: $1\n", {mojom_url_request->content}, nullptr);
  }

  if (!mojom_url_request->content_type.empty()) {
    log += base::ReplaceStringPlaceholders(
        "  Content Type: $1\n", {mojom_url_request->content_type}, nullptr);
  }

  std::ostringstream ss;
  ss << mojom_url_request->method;
  log += "  Method: " + ss.str();

  return log;
}

std::string UrlRequestHeadersToString(
    const mojom::UrlRequestInfoPtr& mojom_url_request) {
  std::string log = "  Headers:\n";

  if (!mojom_url_request->headers.empty()) {
    log += HeadersToString(mojom_url_request->headers);
  }

  return log;
}

}  // namespace catsxp_ads
