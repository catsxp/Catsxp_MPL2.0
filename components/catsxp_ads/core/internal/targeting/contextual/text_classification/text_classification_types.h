/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TYPES_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/containers/circular_deque.h"

namespace catsxp_ads {

using TextClassificationProbabilityMap =
    std::map</*segment*/ std::string, /*page_score*/ double>;
using TextClassificationProbabilityList =
    base::circular_deque<TextClassificationProbabilityMap>;

using SegmentProbabilityPair =
    std::pair</*segment*/ std::string, /*probability*/ double>;
using SegmentProbabilityList = std::vector<SegmentProbabilityPair>;
using SegmentProbabilityMap =
    std::map</*segment*/ std::string, /*page_score*/ double>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_TYPES_H_
