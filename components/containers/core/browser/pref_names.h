/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREF_NAMES_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREF_NAMES_H_

namespace containers::prefs {

// Controls whether Containers feature (menus, management UI) is available;
// existing container tabs are not affected when the pref is disabled.
inline constexpr char kContainersEnabled[] = "catsxp.containers.enabled";

// Syncable list of containers.
inline constexpr char kContainersList[] = "catsxp.containers.list";

// Local-only dictionary of container snapshots that are still referenced by
// this profile even if they disappear from the synced containers list.
inline constexpr char kLocallyUsedContainers[] = "catsxp.containers.used";

}  // namespace containers::prefs

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREF_NAMES_H_
