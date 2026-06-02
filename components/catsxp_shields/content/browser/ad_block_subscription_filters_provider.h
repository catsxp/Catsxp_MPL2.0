/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_

#include <string>

#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/trace_event/trace_event.h"
#include "catsxp/components/catsxp_component_updater/browser/dat_file_util.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider.h"
#include "catsxp/components/catsxp_shields/core/browser/ad_block_filters_provider_manager.h"
#include "catsxp/components/catsxp_shields/core/common/adblock/rs/src/lib.rs.h"
#include "third_party/rust/cxx/v1/cxx.h"

using catsxp_component_updater::DATFileDataBuffer;

namespace adblock {
struct FilterListMetadata;
}  // namespace adblock

namespace catsxp_shields {

class AdBlockSubscriptionFiltersProvider : public AdBlockFiltersProvider {
 public:
  AdBlockSubscriptionFiltersProvider(
      AdBlockFiltersProviderManager* manager,
      base::FilePath list_file,
      base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
          on_metadata_retrieved);
  AdBlockSubscriptionFiltersProvider(
      const AdBlockSubscriptionFiltersProvider&) = delete;
  AdBlockSubscriptionFiltersProvider& operator=(
      const AdBlockSubscriptionFiltersProvider&) = delete;
  ~AdBlockSubscriptionFiltersProvider() override;

  void LoadFilterSet(
      base::OnceCallback<void(
          base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)>) override;

  void OnListAvailable();

 private:
  void OnDATFileDataReady(
      base::OnceCallback<
          void(base::OnceCallback<void(rust::Box<adblock::FilterSet>*)>)> cb,
      const perfetto::Flow& flow,
      const DATFileDataBuffer& dat_buf);

  std::string GetNameForDebugging() override;

  base::FilePath list_file_;

  base::RepeatingCallback<void(const adblock::FilterListMetadata&)>
      on_metadata_retrieved_;

  base::WeakPtrFactory<AdBlockSubscriptionFiltersProvider> weak_factory_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_FILTERS_PROVIDER_H_
