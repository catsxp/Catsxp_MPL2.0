/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/test/creative_set_conversion_test_util.h"

#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_database_util.h"
#include "catsxp/components/catsxp_ads/core/internal/creatives/conversions/creative_set_conversion_info.h"

namespace catsxp_ads::test {

CreativeSetConversionInfo BuildCreativeSetConversion(
    const std::string& creative_set_id,
    const std::string& url_pattern,
    base::TimeDelta observation_window) {
  CreativeSetConversionInfo creative_set_conversion;

  creative_set_conversion.id = creative_set_id;
  creative_set_conversion.url_pattern = url_pattern;
  creative_set_conversion.observation_window = observation_window;
  creative_set_conversion.expire_at =
      Now() + creative_set_conversion.observation_window;

  return creative_set_conversion;
}

void BuildAndSaveCreativeSetConversion(const std::string& creative_set_id,
                                       const std::string& url_pattern,
                                       base::TimeDelta observation_window) {
  CreativeSetConversionList creative_set_conversions;

  creative_set_conversions.push_back(BuildCreativeSetConversion(
      creative_set_id, url_pattern, observation_window));

  database::SaveCreativeSetConversions(creative_set_conversions);
}

}  // namespace catsxp_ads::test
