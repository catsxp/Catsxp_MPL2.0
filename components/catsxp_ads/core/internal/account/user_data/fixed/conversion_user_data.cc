/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/conversion_user_data.h"


#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/conversion_user_data_constants.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/conversion_user_data_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"

namespace catsxp_ads {

base::DictValue BuildConversionUserData(const ConversionInfo& conversion) {
  base::ListValue list;

  // Conversion.
  list.Append(BuildConversionActionTypeUserData(conversion));

  return base::DictValue().Set(kConversionKey, std::move(list));
}

}  // namespace catsxp_ads
