/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_UNKNOWN_CONTAINER_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_UNKNOWN_CONTAINER_H_

#include <string_view>

#include "catsxp/components/containers/core/mojom/containers.mojom-forward.h"
#include "third_party/skia/include/core/SkColor.h"

namespace containers {

// Background color to represent an unknown container.
inline constexpr SkColor kUnknownContainerBackgroundColor =
    SkColorSetRGB(0xb7, 0x4d, 0x49);

// Builds an "unknown" Container for the given `container_id`. The unknown
// container is a placeholder for a container that is not present in the synced
// and locally used lists. This exists to handle unknown containers gracefully
// at runtime.
mojom::ContainerPtr CreateUnknownContainer(std::string_view container_id);

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_UNKNOWN_CONTAINER_H_
