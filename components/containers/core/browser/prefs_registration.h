/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREFS_REGISTRATION_H_
#define CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREFS_REGISTRATION_H_

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace containers {

// Registers container-related preferences with the profile's preference system.
void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

}  // namespace containers

#endif  // CATSXP_COMPONENTS_CONTAINERS_CORE_BROWSER_PREFS_REGISTRATION_H_
