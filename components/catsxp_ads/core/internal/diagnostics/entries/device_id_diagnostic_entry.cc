/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/diagnostics/entries/device_id_diagnostic_entry.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr char kName[] = "Device Id";
constexpr char kUnknown[] = "Unknown";

}  // namespace

DiagnosticEntryType DeviceIdDiagnosticEntry::GetType() const {
  return DiagnosticEntryType::kDeviceId;
}

std::string DeviceIdDiagnosticEntry::GetName() const {
  return kName;
}

std::string DeviceIdDiagnosticEntry::GetValue() const {
  const auto& sys_info = GlobalState::GetInstance()->SysInfo();
  const std::string& device_id = sys_info.device_id;

  if (device_id.empty()) {
    return kUnknown;
  }

  return device_id;
}

}  // namespace catsxp_ads
