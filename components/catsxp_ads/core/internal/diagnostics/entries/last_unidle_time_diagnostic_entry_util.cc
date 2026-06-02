/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry_util.h"

#include <memory>
#include <utility>

#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/diagnostic_manager.h"
#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/last_unidle_time_diagnostic_entry.h"

namespace catsxp_ads {

void SetLastUnIdleTimeDiagnosticEntry(base::Time last_unidle_at) {
  auto last_unidle_time_diagnostic_entry =
      std::make_unique<LastUnIdleTimeDiagnosticEntry>(last_unidle_at);

  DiagnosticManager::GetInstance().SetEntry(
      std::move(last_unidle_time_diagnostic_entry));
}

}  // namespace catsxp_ads
