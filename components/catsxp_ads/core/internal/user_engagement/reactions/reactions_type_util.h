/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

mojom::ReactionType ToggleLikedReactionType(
    mojom::ReactionType mojom_reaction_type);

mojom::ReactionType ToggleDislikedReactionType(
    mojom::ReactionType mojom_reaction_type);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_REACTIONS_REACTIONS_TYPE_UTIL_H_
