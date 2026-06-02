/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_TEST_CREATIVE_SET_CONVERSION_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_TEST_CREATIVE_SET_CONVERSION_TEST_UTIL_H_

#include <string>

namespace base {
class TimeDelta;
}  // namespace base

namespace catsxp_ads {

struct CreativeSetConversionInfo;

namespace test {

CreativeSetConversionInfo BuildCreativeSetConversion(
    const std::string& creative_set_id,
    const std::string& url_pattern,
    base::TimeDelta observation_window);
void BuildAndSaveCreativeSetConversion(const std::string& creative_set_id,
                                       const std::string& url_pattern,
                                       base::TimeDelta observation_window);

}  // namespace test

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CREATIVES_CONVERSIONS_TEST_CREATIVE_SET_CONVERSION_TEST_UTIL_H_
