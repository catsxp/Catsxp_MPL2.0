/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CONTENT_BROWSER_TAB_RESTORE_UTILS_H_
#define CATSXP_COMPONENTS_CONTAINERS_CONTENT_BROWSER_TAB_RESTORE_UTILS_H_

#include <optional>

#include "base/component_export.h"
#include "base/containers/span.h"

namespace content {
class BrowserContext;
class StoragePartitionConfig;
}  // namespace content

namespace sessions {
class SerializedNavigationEntry;
}  // namespace sessions

namespace containers {

// Returns the StoragePartitionConfig to use when restoring a tab from session
// data. Examines the selected navigation entry for container storage partition
// info and, if found, creates the corresponding StoragePartitionConfig.
// Returns std::nullopt if the Containers feature is disabled, navigations are
// empty, the selected index is out of range, or the navigation doesn't belong
// to a container.
COMPONENT_EXPORT(CONTAINERS_CONTENT_BROWSER_TAB_RESTORE)
std::optional<content::StoragePartitionConfig>
GetStoragePartitionConfigToRestore(
    content::BrowserContext* browser_context,
    base::span<const sessions::SerializedNavigationEntry> navigations,
    int selected_navigation);

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CONTENT_BROWSER_TAB_RESTORE_UTILS_H_
