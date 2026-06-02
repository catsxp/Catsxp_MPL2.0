/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_

namespace base {
class DictValue;
}  // namespace base

namespace catsxp_ads {

struct AdHistoryItemInfo;

void ParseCreatedAt(const base::DictValue& dict,
                    AdHistoryItemInfo& ad_history_item);

void ParseAdContent(const base::DictValue& dict,
                    AdHistoryItemInfo& ad_history_item);

void ParseSegmentContent(const base::DictValue& dict,
                         AdHistoryItemInfo& ad_history_item);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_HISTORY_AD_HISTORY_VALUE_UTIL_INTERNAL_H_
