/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_SERVICE_OBSERVER_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_SERVICE_OBSERVER_H_

#include "base/observer_list_types.h"

namespace containers {

// Observes `ContainersService` for changes to the user-editable containers list
// (backed by prefs).
class ContainersServiceObserver : public base::CheckedObserver {
 public:
  // Called when the synced containers list pref changes.
  virtual void OnContainersListChanged() {}
};

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_CONTAINERS_SERVICE_OBSERVER_H_
