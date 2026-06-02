/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_TEMPORARY_CONTAINER_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_TEMPORARY_CONTAINER_H_

#include <string_view>

#include "catsxp/components/containers/core/mojom/containers.mojom-forward.h"

namespace containers {

// Prefix for temporary container ids.
inline constexpr std::string_view kTemporaryContainerIdPrefix = "t-";

// Checks if a given container id is a temporary container id.
bool IsTemporaryContainerId(std::string_view container_id);

// Builds a temporary container (`t-` prefixed container id, BIP-39 two-word
// name, random icon, random background color).
mojom::ContainerPtr CreateTemporaryContainer();

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_TEMPORARY_CONTAINER_H_
