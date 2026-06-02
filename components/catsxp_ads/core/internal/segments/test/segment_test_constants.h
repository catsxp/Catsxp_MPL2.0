/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_TEST_SEGMENT_TEST_CONSTANTS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_TEST_SEGMENT_TEST_CONSTANTS_H_

#include <array>
#include <string_view>

namespace catsxp_ads::test {

inline constexpr auto kSegments =
    std::to_array<std::string_view>({"architecture",
                                     "arts & entertainment",
                                     "automotive",
                                     "business",
                                     "careers",
                                     "cell phones",
                                     "crypto",
                                     "education",
                                     "family & parenting",
                                     "fashion",
                                     "folklore",
                                     "food & drink",
                                     "gaming",
                                     "health & fitness",
                                     "history",
                                     "hobbies & interests",
                                     "home",
                                     "law",
                                     "military",
                                     "other",
                                     "personal finance",
                                     "pets",
                                     "real estate",
                                     "science",
                                     "sports",
                                     "technology & computing",
                                     "travel",
                                     "weather"});

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SEGMENTS_TEST_SEGMENT_TEST_CONSTANTS_H_
