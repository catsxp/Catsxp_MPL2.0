/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_CONTAINERS_USED_CONTAINER_STORAGE_PARTITIONS_H_
#define CATSXP_BROWSER_CONTAINERS_USED_CONTAINER_STORAGE_PARTITIONS_H_

#include <vector>

#include "content/public/browser/storage_partition_config.h"

class Profile;

namespace containers {

// Returns StoragePartitionConfig for each locally used container. Returns an
// empty vector when the ContainersService is unavailable.
std::vector<content::StoragePartitionConfig>
GetUsedContainerStoragePartitionConfigs(Profile* profile);

}  // namespace containers

#endif  // CATSXP_BROWSER_CONTAINERS_USED_CONTAINER_STORAGE_PARTITIONS_H_
