/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_PARSER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_PARSER_H_

#include <optional>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"

namespace catsxp_ads::json::reader {

// Parses the confirmation queue from the legacy `confirmations.json` format.
std::optional<ConfirmationList> ParseConfirmations(std::string_view json);

}  // namespace catsxp_ads::json::reader

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_LEGACY_MIGRATION_CONFIRMATIONS_LEGACY_CONFIRMATION_MIGRATION_CONFIRMATIONS_JSON_PARSER_H_
