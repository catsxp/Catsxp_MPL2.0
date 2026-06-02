/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINER_SPECIFIER_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINER_SPECIFIER_H_

#include <string>
#include <variant>

#include "base/types/strong_alias.h"

namespace containers {

// Strong alias for container id.
using ContainerId = base::StrongAlias<class ContainerIdTag, std::string>;
// Strong alias for container name.
using ContainerName = base::StrongAlias<class ContainerNameTag, std::string>;

// A variant of container id or name used to represent a container.
using ContainerSpecifier =
    std::variant<std::monostate, ContainerId, ContainerName>;

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINER_SPECIFIER_H_
