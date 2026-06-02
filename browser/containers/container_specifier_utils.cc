/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/containers/container_specifier_utils.h"

#include "base/logging.h"
#include "catsxp/browser/containers/containers_service_factory.h"
#include "catsxp/components/containers/content/browser/storage_partition_utils.h"
#include "catsxp/components/containers/core/browser/containers_service.h"
#include "catsxp/components/containers/core/common/features.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/navigator/browser_navigator_params.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition_config.h"

namespace containers {
namespace {

constexpr char kContainerIdKey[] = "container_id";

}  // namespace

void SerializeContainerSpecifier(content::WebContents* web_contents,
                                 base::Value& value) {
  if (!base::FeatureList::IsEnabled(features::kContainers)) {
    return;
  }

  CHECK(value.is_dict());
  if (std::string container_id = GetContainerIdForWebContents(web_contents);
      !container_id.empty()) {
    value.GetDict().Set(kContainerIdKey, base::Value(container_id));
  }
}

void DeserializeContainerSpecifier(const base::Value& value,
                                   ContainerSpecifier& container_specifier) {
  if (!base::FeatureList::IsEnabled(features::kContainers)) {
    return;
  }

  if (!value.is_dict()) {
    LOG(ERROR) << "value is not a dictionary";
    return;
  }

  if (const std::string* container_id =
          value.GetDict().FindString(kContainerIdKey)) {
    container_specifier = ContainerId(*container_id);
  }
}

std::optional<content::StoragePartitionConfig>
GetStoragePartitionConfigForContainerSpecifier(
    content::BrowserContext* browser_context,
    const ContainerSpecifier& container_specifier) {
  if (!base::FeatureList::IsEnabled(features::kContainers)) {
    return std::nullopt;
  }

  // If the container specifier is not set, return nullopt.
  if (std::holds_alternative<std::monostate>(container_specifier)) {
    return std::nullopt;
  }

  auto* containers_service = ContainersServiceFactory::GetForProfile(
      Profile::FromBrowserContext(browser_context));
  if (!containers_service) {
    return std::nullopt;
  }

  if (auto container_id =
          containers_service->GetContainerIdFromContainerSpecifier(
              container_specifier)) {
    return content::StoragePartitionConfig::Create(
        browser_context, kContainersStoragePartitionDomain, *container_id,
        browser_context->IsOffTheRecord());
  }

  return std::nullopt;
}

}  // namespace containers
