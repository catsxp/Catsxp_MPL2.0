/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_types.h"

namespace catsxp_ads {

KeywordList ParseKeyphrase(const std::string& keyphrase);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_KEYPHRASE_PURCHASE_INTENT_KEYPHRASE_PARSER_H_
