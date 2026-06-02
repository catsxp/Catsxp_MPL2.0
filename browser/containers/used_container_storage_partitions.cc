/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/containers/used_container_storage_partitions.h"

#include <string>

#include "base/check.h"
#include "base/containers/to_vector.h"
#include "catsxp/browser/containers/containers_service_factory.h"
#include "catsxp/components/containers/content/browser/storage_partition_utils.h"
#include "catsxp/components/containers/core/browser/containers_service.h"
#include "catsxp/components/containers/core/common/features.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/storage_partition_config.h"

namespace containers {

std::vector<content::StoragePartitionConfig>
GetUsedContainerStoragePartitionConfigs(Profile* profile) {
  CHECK(base::FeatureList::IsEnabled(features::kContainers));

  if (!profile) {
    return {};
  }

  ContainersService* service = ContainersServiceFactory::GetForProfile(profile);
  if (!service) {
    return {};
  }

  return base::ToVector(service->GetUsedContainerIds(),
                        [&](const std::string& id) {
                          return content::StoragePartitionConfig::Create(
                              profile, kContainersStoragePartitionDomain, id,
                              profile->IsOffTheRecord());
                        });
}

}  // namespace containers
