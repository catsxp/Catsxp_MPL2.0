/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/ad_block_resource_provider.h"

namespace catsxp_shields {

AdBlockResourceProvider::AdBlockResourceProvider() = default;

AdBlockResourceProvider::~AdBlockResourceProvider() = default;

void AdBlockResourceProvider::AddObserver(
    AdBlockResourceProvider::Observer* observer) {
  if (!observers_.HasObserver(observer)) {
    observers_.AddObserver(observer);
  }
}

void AdBlockResourceProvider::RemoveObserver(
    AdBlockResourceProvider::Observer* observer) {
  if (observers_.HasObserver(observer)) {
    observers_.RemoveObserver(observer);
  }
}

void AdBlockResourceProvider::NotifyResourcesLoaded(
    AdblockResourceStorageBox storage) {
  for (auto& observer : observers_) {
    observer.OnResourcesLoaded(adblock::clone_resource_storage(*storage));
  }
}

}  // namespace catsxp_shields
