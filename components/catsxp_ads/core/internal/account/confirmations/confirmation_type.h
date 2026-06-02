/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_

#include <string_view>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

// Returns a `mojom::ConfirmationType` value based on the string input.
mojom::ConfirmationType ToMojomConfirmationType(std::string_view value);

// Returns a string constant for a given `mojom::ConfirmationType` value.
std::string_view ToString(mojom::ConfirmationType value);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_
