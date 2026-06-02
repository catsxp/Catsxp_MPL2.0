/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_type_util.h"

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

mojom::ReactionType ToggleLikedReactionType(
    mojom::ReactionType mojom_reaction_type) {
  switch (mojom_reaction_type) {
    case mojom::ReactionType::kNeutral:
    case mojom::ReactionType::kDisliked: {
      // If the reaction is neutral or disliked, toggle to liked.
      return mojom::ReactionType::kLiked;
    }

    case mojom::ReactionType::kLiked: {
      // If the reaction is liked, toggle to neutral.
      return mojom::ReactionType::kNeutral;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::ReactionType: "
               << mojom_reaction_type;
}

mojom::ReactionType ToggleDislikedReactionType(
    mojom::ReactionType mojom_reaction_type) {
  switch (mojom_reaction_type) {
    case mojom::ReactionType::kNeutral:
    case mojom::ReactionType::kLiked: {
      // If the reaction is neutral or liked, toggle to disliked.
      return mojom::ReactionType::kDisliked;
    }

    case mojom::ReactionType::kDisliked: {
      // If the reaction is disliked, toggle to neutral.
      return mojom::ReactionType::kNeutral;
    }
  }

  NOTREACHED() << "Unexpected value for mojom::ReactionType: "
               << mojom_reaction_type;
}

}  // namespace catsxp_ads
