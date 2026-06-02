/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_value_util.h"

#include <string_view>

#include "base/check.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kNameKey = "name";
constexpr std::string_view kValueKey = "value";

}  // namespace

base::ListValue DiagnosticsToList(const DiagnosticMap& diagnostics) {
  base::ListValue list;

  for (const auto& [_, entry] : diagnostics) {
    CHECK(entry);

    list.Append(base::DictValue()
                    .Set(kNameKey, entry->GetName())
                    .Set(kValueKey, entry->GetValue()));
  }

  return list;
}

}  // namespace catsxp_ads
