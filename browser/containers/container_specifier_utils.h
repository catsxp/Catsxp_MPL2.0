/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CONTAINERS_CONTAINER_SPECIFIER_UTILS_H_
#define CATSXP_BROWSER_CONTAINERS_CONTAINER_SPECIFIER_UTILS_H_

#include <optional>

#include "base/values.h"
#include "catsxp/components/containers/core/browser/container_specifier.h"

namespace content {
class BrowserContext;
class StoragePartitionConfig;
class WebContents;
}  // namespace content

namespace containers {

// Serializes the container specifier for the given web contents into the value.
void SerializeContainerSpecifier(content::WebContents* web_contents,
                                 base::Value& value);

// Deserializes the container specifier from the value into the container
// specifier.
void DeserializeContainerSpecifier(const base::Value& value,
                                   ContainerSpecifier& container_specifier);

// Returns the storage partition config for the given container specifier.
std::optional<content::StoragePartitionConfig>
GetStoragePartitionConfigForContainerSpecifier(
    content::BrowserContext* browser_context,
    const ContainerSpecifier& container_specifier);

}  // namespace containers

#endif  // CATSXP_BROWSER_CONTAINERS_CONTAINER_SPECIFIER_UTILS_H_
