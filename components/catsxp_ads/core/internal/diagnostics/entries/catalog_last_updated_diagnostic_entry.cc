/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/catalog_last_updated_diagnostic_entry.h"

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"

namespace catsxp_ads {

namespace {
constexpr char kName[] = "Catalog last updated";
}  // namespace

DiagnosticEntryType CatalogLastUpdatedDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kCatalogLastUpdated;
}

std::string CatalogLastUpdatedDiagnosticEntry::GetName() const {
  return kName;
}

std::string CatalogLastUpdatedDiagnosticEntry::GetValue() const {
  const base::Time last_updated_at = GetCatalogLastUpdated();
  if (last_updated_at.is_null()) {
    return {};
  }

  return LongFriendlyDateAndTime(last_updated_at,
                                 /*use_sentence_style=*/false);
}

}  // namespace catsxp_ads
