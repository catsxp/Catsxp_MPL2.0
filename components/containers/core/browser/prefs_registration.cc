/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/containers/core/browser/prefs_registration.h"

#include "catsxp/components/containers/core/browser/default_containers_list.h"
#include "catsxp/components/containers/core/browser/pref_names.h"
#include "catsxp/components/containers/core/browser/prefs.h"
#include "components/pref_registry/pref_registry_syncable.h"

namespace containers {

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(prefs::kContainersEnabled, true);
  registry->RegisterListPref(
      prefs::kContainersList,
      ConvertContainersToListValue(CreateDefaultContainersList()),
      user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
  registry->RegisterDictionaryPref(prefs::kLocallyUsedContainers);
}

}  // namespace containers
