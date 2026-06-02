/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

// KeywordList type alias separated from the keyphrase parser so that struct
// headers needing only the type do not pull in ParseKeyphrase().

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_TYPES_H_

#include <string>
#include <vector>

namespace catsxp_ads {

using KeywordList = std::vector<std::string>;

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_TYPES_H_
