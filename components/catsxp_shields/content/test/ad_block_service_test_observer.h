/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_SERVICE_TEST_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_SERVICE_TEST_OBSERVER_H_

#include "base/run_loop.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_shields/content/browser/ad_block_service.h"

namespace catsxp_shields {

// Blocking waiter for AdBlockService filter-list load events. Observes
// AdBlockService::Observer::OnFilterListLoaded which fires on the UI sequence,
// avoiding the cross-sequence race the engine-scoped test observer suffered
// from. Single-use per engine.
class AdBlockServiceTestObserver : public AdBlockService::Observer {
 public:
  explicit AdBlockServiceTestObserver(AdBlockService* service);
  AdBlockServiceTestObserver(const AdBlockServiceTestObserver&) = delete;
  AdBlockServiceTestObserver& operator=(const AdBlockServiceTestObserver&) =
      delete;
  ~AdBlockServiceTestObserver() override;

  // Blocks until OnFilterListLoaded fires for the specified engine. Quit is
  // latched so the event may fire before or after the call; Wait returns in
  // either case.
  void WaitForDefault();
  void WaitForAdditional();

  // Convenience for callers with a dynamic engine choice.
  void Wait(bool is_default_engine);

 private:
  // AdBlockService::Observer:
  void OnFilterListLoaded(bool is_default_engine,
                          AdBlockService::FilterListLoadResult result) override;

  base::RunLoop default_loop_;
  base::RunLoop additional_loop_;
  base::ScopedObservation<AdBlockService, AdBlockService::Observer>
      observation_{this};
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_SERVICE_TEST_OBSERVER_H_
