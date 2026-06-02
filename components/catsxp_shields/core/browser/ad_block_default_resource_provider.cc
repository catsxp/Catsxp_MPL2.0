/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/ad_block_default_resource_provider.h"

#include <string>
#include <utility>

#include "base/files/file_path.h"
#include "base/task/thread_pool.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_component_installer.h"

namespace {

constexpr char kAdBlockResourcesFilename[] = "resources.json";

}  // namespace

namespace catsxp_shields {

AdBlockDefaultResourceProvider::AdBlockDefaultResourceProvider(
    component_updater::ComponentUpdateService* cus) {
  // Can be nullptr in unit tests
  if (!cus) {
    return;
  }

  RegisterAdBlockDefaultResourceComponent(
      cus,
      base::BindRepeating(&AdBlockDefaultResourceProvider::OnComponentReady,
                          weak_factory_.GetWeakPtr()));
}

AdBlockDefaultResourceProvider::~AdBlockDefaultResourceProvider() = default;

base::FilePath AdBlockDefaultResourceProvider::GetResourcesPath() {
  if (component_path_.empty()) {
    // Since we know it's empty return it as is.
    return component_path_;
  }

  return component_path_.AppendASCII(kAdBlockResourcesFilename);
}

void AdBlockDefaultResourceProvider::OnComponentReady(
    const base::FilePath& path) {
  component_path_ = path;
  base::FilePath resources_path = GetResourcesPath();

  if (resources_path.empty()) {
    // This should not happen, but if it does, we should not proceed.
    return;
  }

  // Load the resources (as ResourceStorage)
  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(&catsxp_component_updater::GetDATFileAsString,
                     resources_path),
      base::BindOnce(
          [](base::WeakPtr<AdBlockDefaultResourceProvider> provider,
             const std::string& resources_json) {
            if (!provider) {
              return;
            }
            auto storage = adblock::new_resource_storage(resources_json);
            provider->NotifyResourcesLoaded(std::move(storage));
          },
          weak_factory_.GetWeakPtr()));
}

void AdBlockDefaultResourceProvider::LoadResources(
    base::OnceCallback<void(AdblockResourceStorageBox)> cb) {
  base::FilePath resources_path = GetResourcesPath();
  if (resources_path.empty()) {
    // If the path is not ready yet, run the callback with empty resources to
    // avoid blocking filter data loads.
    auto empty_storage = adblock::new_empty_resource_storage();
    std::move(cb).Run(std::move(empty_storage));
    return;
  }

  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(&catsxp_component_updater::GetDATFileAsString,
                     resources_path),
      base::BindOnce(
          [](base::OnceCallback<void(AdblockResourceStorageBox)> cb,
             const std::string& resources_json) {
            auto storage = adblock::new_resource_storage(resources_json);
            std::move(cb).Run(std::move(storage));
          },
          std::move(cb)));
}

}  // namespace catsxp_shields
