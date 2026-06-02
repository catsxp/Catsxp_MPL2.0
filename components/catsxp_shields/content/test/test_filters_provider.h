/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_TEST_FILTERS_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_TEST_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace catsxp_shields {

class AdBlockFiltersProviderManager;
class AdBlockService;

class TestFiltersProvider : public AdBlockFiltersProvider {
 public:
  explicit TestFiltersProvider(const std::string& rules);
  TestFiltersProvider(const std::string& rules,
                      bool engine_is_default,
                      uint8_t permission_mask = 0);
  ~TestFiltersProvider() override;

  void RegisterAsSourceProvider(AdBlockService* ad_block_service);
  void RegisterAsSourceProvider(AdBlockFiltersProviderManager* manager);

  void LoadFilterSet(
      base::OnceCallback<void(
          base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) override;

  void Initialize();
  bool IsInitialized() const override;

  std::string GetNameForDebugging() override;

  // Simulates a provider content change for testing.
  void SimulateUpdate() { NotifyObservers(engine_is_default_); }

 private:
  std::string rules_;
  uint8_t permission_mask_;
  bool is_initialized_;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_TEST_FILTERS_PROVIDER_H_
