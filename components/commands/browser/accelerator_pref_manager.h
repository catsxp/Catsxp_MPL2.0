/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_COMMANDS_BROWSER_ACCELERATOR_PREF_MANAGER_H_
#define CATSXP_COMPONENTS_COMMANDS_BROWSER_ACCELERATOR_PREF_MANAGER_H_

#include <vector>

#include "base/component_export.h"
#include "base/containers/flat_map.h"
#include "base/containers/flat_set.h"
#include "base/containers/span.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "ui/base/accelerators/accelerator.h"

namespace commands {

class COMPONENT_EXPORT(COMMANDS_BROWSER) AcceleratorPrefManager {
 public:
  using Accelerators = base::flat_map<int, std::vector<ui::Accelerator>>;

  static void RegisterProfilePrefs(PrefRegistrySimple* registry);

  explicit AcceleratorPrefManager(PrefService* prefs,
                                  base::span<const int> available_command_ids);
  AcceleratorPrefManager(const AcceleratorPrefManager&) = delete;
  AcceleratorPrefManager& operator=(const AcceleratorPrefManager&) = delete;
  ~AcceleratorPrefManager();

  void ClearAccelerators(int command_id);
  void AddAccelerator(int command_id, const ui::Accelerator& accelerator);
  void RemoveAccelerator(int command_id, const ui::Accelerator& accelerator);

  Accelerators GetAccelerators();
  Accelerators GetDefaultAccelerators();
  void SetDefaultAccelerators(const Accelerators& default_accelerators);

 private:
  raw_ptr<PrefService> prefs_;
  base::flat_set<int> available_command_ids_;
};

}  // namespace commands

#endif  // CATSXP_COMPONENTS_COMMANDS_BROWSER_ACCELERATOR_PREF_MANAGER_H_
