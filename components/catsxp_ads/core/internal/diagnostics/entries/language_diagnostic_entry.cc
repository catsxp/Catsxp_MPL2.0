/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/language_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/public/common/locale/locale_util.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Language";
}  // namespace

DiagnosticEntryType LanguageDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kLanguage;
}

std::string LanguageDiagnosticEntry::GetName() const {
  return kName;
}

std::string LanguageDiagnosticEntry::GetValue() const {
  return CurrentLanguageCode();
}

}  // namespace catsxp_ads
