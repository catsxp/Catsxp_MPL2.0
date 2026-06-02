/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/browser/ad_block_custom_filter_reset_util.h"

#include <array>

#include "base/strings/strcat.h"
#include "base/strings/string_util.h"
#include "net/http/http_util.h"

namespace catsxp_shields {

namespace {
constexpr auto kCustomFilterPatternsToSkip = std::to_array<std::string_view>(
    {// Scriptlets
     "+js(",

     // Procedural cosmetic filters
     ":has(", ":has-text(", ":matches-attr(", ":matches-css(",
     ":matches-css-before(", ":matches-css-after(", ":matches-media(",
     ":matches-path(", ":matches-prop(", ":min-text-length(", ":not(",
     ":others(", ":upward(", ":watch-attr(", ":xpath("});

bool IsInAllowList(std::string_view custom_filter_line) {
  for (std::string_view pattern : kCustomFilterPatternsToSkip) {
    if (custom_filter_line.find(pattern) != std::string::npos) {
      return true;
    }
  }
  return false;
}

}  // namespace

std::optional<std::string> ResetCustomFiltersForHost(
    std::string_view host,
    std::string_view custom_filters) {
  if (host.empty() || custom_filters.empty()) {
    return std::nullopt;
  }

  std::string result;
  const auto starts_with_str = base::StrCat({host, "##"});
  base::StringViewTokenizer tokenizer(custom_filters, "\n");
  while (tokenizer.GetNext()) {
    std::string_view token =
        base::TrimWhitespaceASCII(tokenizer.token(), base::TRIM_ALL);
    if (token.starts_with(starts_with_str) && !IsInAllowList(token)) {
      continue;  // Exclude line from the result
    }
    result.append(base::StrCat({token, "\n"}));
  }
  return result;
}

bool IsCustomFiltersAvailable(std::string_view host,
                              std::string_view custom_filters) {
  if (host.empty() || custom_filters.empty()) {
    return false;
  }

  const auto starts_with_str = base::StrCat({host, "##"});
  base::StringViewTokenizer tokenizer(custom_filters, "\n");
  while (tokenizer.GetNext()) {
    std::string_view token =
        base::TrimWhitespaceASCII(tokenizer.token(), base::TRIM_ALL);
    if (token.starts_with(starts_with_str) && !IsInAllowList(token)) {
      return true;
    }
  }
  return false;
}

}  // namespace catsxp_shields
