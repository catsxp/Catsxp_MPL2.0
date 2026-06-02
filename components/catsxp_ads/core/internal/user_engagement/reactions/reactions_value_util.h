/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_VALUE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_VALUE_UTIL_H_

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions.h"

namespace catsxp_ads {

base::DictValue ReactionMapToDict(const ReactionMap& reactions);
ReactionMap ReactionMapFromDict(const base::DictValue& dict);

base::ListValue ReactionSetToList(const ReactionSet& reactions);
ReactionSet ReactionSetFromList(const base::ListValue& list);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_VALUE_UTIL_H_
