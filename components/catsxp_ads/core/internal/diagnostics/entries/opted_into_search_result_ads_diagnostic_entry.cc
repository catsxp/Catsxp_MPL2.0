/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/opted_into_search_result_ads_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_conversions_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Opted into search result ads";
}  // namespace

DiagnosticEntryType OptedInToSearchResultAdsDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kOptedInToSearchResultAds;
}

std::string OptedInToSearchResultAdsDiagnosticEntry::GetName() const {
  return kName;
}

std::string OptedInToSearchResultAdsDiagnosticEntry::GetValue() const {
  return BoolToString(UserHasOptedInToSearchResultAds());
}

}  // namespace catsxp_ads
