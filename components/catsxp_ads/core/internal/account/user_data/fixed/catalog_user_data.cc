/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/catalog_user_data.h"

#include <string_view>

#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kCatalogKey = "catalog";
constexpr std::string_view kIdKey = "id";

}  // namespace

base::DictValue BuildCatalogUserData() {
  if (!UserHasJoinedCatsxpRewards()) {
    return {};
  }

  return base::DictValue().Set(
      kCatalogKey,
      base::ListValue().Append(base::DictValue().Set(kIdKey, GetCatalogId())));
}

}  // namespace catsxp_ads
