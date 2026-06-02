/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions_value_util.h"

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

base::DictValue ReactionMapToDict(const ReactionMap& reactions) {
  base::DictValue dict;

  for (const auto& [id, type] : reactions) {
    dict.Set(id, static_cast<int>(type));
  }

  return dict;
}

ReactionMap ReactionMapFromDict(const base::DictValue& dict) {
  ReactionMap reactions;

  for (const auto [id, value] : dict) {
    if (std::optional<int> type = value.GetIfInt()) {
      reactions[id] = static_cast<mojom::ReactionType>(*type);
    }
  }

  return reactions;
}

base::ListValue ReactionSetToList(const ReactionSet& reactions) {
  base::ListValue list;

  for (const auto& reaction : reactions) {
    list.Append(base::Value(reaction));
  }

  return list;
}

ReactionSet ReactionSetFromList(const base::ListValue& list) {
  ReactionSet reactions;

  for (const auto& value : list) {
    if (const std::string* const id = value.GetIfString()) {
      reactions.insert(*id);
    }
  }

  return reactions;
}

}  // namespace catsxp_ads
