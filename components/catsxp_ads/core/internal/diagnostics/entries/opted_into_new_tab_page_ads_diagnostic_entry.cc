/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/opted_into_new_tab_page_ads_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_conversions_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Opted into new tab page ads";
}  // namespace

DiagnosticEntryType OptedInToNewTabPageAdsDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kOptedInToNewTabPageAds;
}

std::string OptedInToNewTabPageAdsDiagnosticEntry::GetName() const {
  return kName;
}

std::string OptedInToNewTabPageAdsDiagnosticEntry::GetValue() const {
  return BoolToString(UserHasOptedInToNewTabPageAds());
}

}  // namespace catsxp_ads
