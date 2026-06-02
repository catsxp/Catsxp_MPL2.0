/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_

#include <string>
#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

ConversionActionType ToConversionActionType(
    mojom::ConfirmationType mojom_confirmation_type);

ConversionActionType ToConversionActionType(std::string_view action_type);

std::string ToString(ConversionActionType action_type);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_
