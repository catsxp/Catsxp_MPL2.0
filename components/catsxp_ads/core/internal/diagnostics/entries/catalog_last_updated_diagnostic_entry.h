/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_CATALOG_LAST_UPDATED_DIAGNOSTIC_ENTRY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_CATALOG_LAST_UPDATED_DIAGNOSTIC_ENTRY_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/diagnostic_entry_interface.h"

namespace catsxp_ads {

class CatalogLastUpdatedDiagnosticEntry final
    : public DiagnosticEntryInterface {
 public:
  // DiagnosticEntryInterface:
  DiagnosticEntryType GetType() const override;
  std::string GetName() const override;
  std::string GetValue() const override;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_CATALOG_LAST_UPDATED_DIAGNOSTIC_ENTRY_H_
