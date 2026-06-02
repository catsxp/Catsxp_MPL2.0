/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"

namespace catsxp_ads {

namespace {

constexpr char kName[] = "Last unidle time";
constexpr char kNever[] = "Never";

}  // namespace
LastUnIdleTimeDiagnosticEntry::LastUnIdleTimeDiagnosticEntry(
    base::Time last_unidle_at) {
  last_unidle_at_ = last_unidle_at;
}

DiagnosticEntryType LastUnIdleTimeDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kLastUnIdleTime;
}

std::string LastUnIdleTimeDiagnosticEntry::GetName() const {
  return kName;
}

std::string LastUnIdleTimeDiagnosticEntry::GetValue() const {
  if (!last_unidle_at_) {
    return kNever;
  }

  return LongFriendlyDateAndTime(*last_unidle_at_,
                                 /*use_sentence_style=*/false);
}

}  // namespace catsxp_ads
