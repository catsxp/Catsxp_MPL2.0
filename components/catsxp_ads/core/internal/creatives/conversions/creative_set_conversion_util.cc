/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_util.h"

#include <algorithm>

#include "base/containers/span.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/conversions_util.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/types/default_conversion/creative_set_conversion_url_pattern/creative_set_conversion_url_pattern_util.h"
#include "url/gurl.h"

namespace catsxp_ads {

CreativeSetConversionList GetMatchingCreativeSetConversions(
    const CreativeSetConversionList& creative_set_conversions,
    base::span<const GURL> redirect_chain) {
  if (creative_set_conversions.empty()) {
    return {};
  }

  CreativeSetConversionList matching_creative_set_conversions;

  std::ranges::copy_if(
      creative_set_conversions,
      std::back_inserter(matching_creative_set_conversions),
      [&redirect_chain](
          const CreativeSetConversionInfo& creative_set_conversion) {
        return DoesCreativeSetConversionUrlPatternMatchRedirectChain(
            creative_set_conversion, redirect_chain);
      });

  return matching_creative_set_conversions;
}

CreativeSetConversionCountMap GetCreativeSetConversionCounts(
    const AdEventList& ad_events) {
  CreativeSetConversionCountMap creative_set_conversion_counts;

  for (const auto& ad_event : ad_events) {
    if (ad_event.confirmation_type == mojom::ConfirmationType::kConversion) {
      ++creative_set_conversion_counts[ad_event.creative_set_id];
    }
  }

  return creative_set_conversion_counts;
}

CreativeSetConversionBucketMap SortCreativeSetConversionsIntoBuckets(
    const CreativeSetConversionList& creative_set_conversions) {
  CreativeSetConversionBucketMap buckets;

  for (const auto& creative_set_conversion : creative_set_conversions) {
    buckets[creative_set_conversion.id].push_back(creative_set_conversion);
  }

  return buckets;
}

void FilterCreativeSetConversionBucketsThatExceedTheCap(
    const std::map<std::string, size_t>& creative_set_conversion_counts,
    size_t creative_set_conversion_cap,
    CreativeSetConversionBucketMap& creative_set_conversion_buckets) {
  if (creative_set_conversion_cap == 0) {
    // No cap.
    return;
  }

  for (const auto& [creative_set_id, creative_set_conversion_count] :
       creative_set_conversion_counts) {
    if (creative_set_conversion_count > creative_set_conversion_cap) {
      creative_set_conversion_buckets.erase(creative_set_id);
    }
  }
}

bool HasCreativeSetConversionWithinObservationWindow(
    const CreativeSetConversionList& creative_set_conversions,
    const AdEventInfo& ad_event) {
  return std::ranges::any_of(
      creative_set_conversions,
      [&ad_event](const CreativeSetConversionInfo& creative_set_conversion) {
        return DidAdEventOccurWithinObservationWindow(
            ad_event, creative_set_conversion.observation_window);
      });
}

}  // namespace catsxp_ads
