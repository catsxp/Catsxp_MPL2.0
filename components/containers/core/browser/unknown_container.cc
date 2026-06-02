/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/containers/core/browser/unknown_container.h"

#include <string>

#include "catsxp/components/containers/core/mojom/containers.mojom.h"

namespace containers {

mojom::ContainerPtr CreateUnknownContainer(std::string_view container_id) {
  // Use first 8 characters of the container ID as the name.
  std::string_view name = container_id.substr(0, 8);
  return mojom::Container::New(std::string(container_id), std::string(name),
                               mojom::Icon::kDefault,
                               kUnknownContainerBackgroundColor);
}

}  // namespace containers
