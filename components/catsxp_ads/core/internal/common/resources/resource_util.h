/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_

#include <optional>
#include <string>

#include "base/functional/callback.h"

namespace catsxp_ads {

template <typename T>
using LoadAndParseResourceComponentCallback =
    base::OnceCallback<void(std::optional<T>)>;

template <typename T>
void LoadAndParseResourceComponent(
    const std::string& id,
    int version,
    LoadAndParseResourceComponentCallback<T> callback);

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_RESOURCES_RESOURCE_UTIL_H_
