/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_VALUE_UTIL_H_

#include "base/values.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

namespace catsxp_ads {

struct AdHistoryItemInfo;

AdHistoryItemInfo AdHistoryItemFromDict(const base::DictValue& dict);

base::DictValue AdHistoryItemToDict(const AdHistoryItemInfo& ad_history_item);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_PUBLIC_HISTORY_AD_HISTORY_ITEM_VALUE_UTIL_H_
