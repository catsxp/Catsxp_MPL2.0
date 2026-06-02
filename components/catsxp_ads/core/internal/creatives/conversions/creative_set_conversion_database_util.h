/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"

namespace catsxp_ads::database {

void PurgeExpiredCreativeSetConversions();

void SaveCreativeSetConversions(
    const CreativeSetConversionList& creative_set_conversions);

}  // namespace catsxp_ads::database

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_DATABASE_UTIL_H_
