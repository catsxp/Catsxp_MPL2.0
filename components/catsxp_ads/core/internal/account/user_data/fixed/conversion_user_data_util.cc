/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/conversion_user_data_util.h"

#include "base/check_op.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/conversion_user_data_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/actions/conversion_action_types_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"

namespace catsxp_ads {

base::DictValue BuildConversionActionTypeUserData(
    const ConversionInfo& conversion) {
  CHECK_NE(ConversionActionType::kUndefined, conversion.action_type);

  return base::DictValue().Set(kConversionActionTypeKey,
                               ToString(conversion.action_type));
}

}  // namespace catsxp_ads
