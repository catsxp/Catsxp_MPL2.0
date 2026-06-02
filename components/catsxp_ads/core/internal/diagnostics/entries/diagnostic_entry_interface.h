/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_entry_types.h"

namespace catsxp_ads {

class DiagnosticEntryInterface {
 public:
  virtual ~DiagnosticEntryInterface() = default;

  // Returns the type of the diagnostic entry, which categorizes the entry for
  // diagnostic purposes.
  virtual DiagnosticEntryType GetType() const = 0;

  // Returns the name of the diagnostic entry, providing a human-readable
  // identifier for this entry.
  virtual std::string GetName() const = 0;

  // Returns the value associated with this diagnostic entry, representing
  // relevant diagnostic data.
  virtual std::string GetValue() const = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_DIAGNOSTICS_ENTRIES_DIAGNOSTIC_ENTRY_INTERFACE_H_
