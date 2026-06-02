/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/country_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Country";
}  // namespace

DiagnosticEntryType CountryDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kCountry;
}

std::string CountryDiagnosticEntry::GetName() const {
  return kName;
}

std::string CountryDiagnosticEntry::GetValue() const {
  return CurrentCountryCode();
}

}  // namespace catsxp_ads
