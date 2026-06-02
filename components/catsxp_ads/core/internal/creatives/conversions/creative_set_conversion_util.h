/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_

#include <cstddef>
#include <map>
#include <string>

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/ad_events/ad_event_info.h"

class GURL;

namespace catsxp_ads {

using CreativeSetConversionBucketMap =
    std::map</*creative_set_id*/ std::string, CreativeSetConversionList>;

using CreativeSetConversionCountMap = std::map</*creative_set_id*/ std::string,
                                               /*count*/ size_t>;

CreativeSetConversionList GetMatchingCreativeSetConversions(
    const CreativeSetConversionList& creative_set_conversions,
    base::span<const GURL> redirect_chain);

CreativeSetConversionCountMap GetCreativeSetConversionCounts(
    const AdEventList& ad_events);

CreativeSetConversionBucketMap SortCreativeSetConversionsIntoBuckets(
    const CreativeSetConversionList& creative_set_conversions);

void FilterCreativeSetConversionBucketsThatExceedTheCap(
    const std::map<std::string, size_t>& creative_set_conversion_counts,
    size_t creative_set_conversion_cap,
    CreativeSetConversionBucketMap& creative_set_conversion_buckets);

bool HasCreativeSetConversionWithinObservationWindow(
    const CreativeSetConversionList& creative_set_conversions,
    const AdEventInfo& ad_event);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_CREATIVE_SET_CONVERSION_UTIL_H_
