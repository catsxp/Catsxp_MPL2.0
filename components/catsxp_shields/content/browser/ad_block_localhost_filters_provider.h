/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/sequence_checker.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider_manager.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace catsxp_shields {

class AdBlockLocalhostFiltersProvider : public AdBlockFiltersProvider {
 public:
  explicit AdBlockLocalhostFiltersProvider(
      AdBlockFiltersProviderManager* manager);
  ~AdBlockLocalhostFiltersProvider() override;
  AdBlockLocalhostFiltersProvider(const AdBlockLocalhostFiltersProvider&) =
      delete;
  AdBlockLocalhostFiltersProvider& operator=(
      const AdBlockLocalhostFiltersProvider&) = delete;

  std::string GetLocalhostFilters();
  bool UpdateLocalhostFilters(const std::string& localhost_filters);

  // AdBlockFiltersProvider
  void LoadFilterSet(
      base::OnceCallback<void(
          base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) override;

  std::string GetNameForDebugging() override;

 private:
  SEQUENCE_CHECKER(sequence_checker_);
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_LOCALHOST_FILTERS_PROVIDER_H_
