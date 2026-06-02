/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/content/test/ad_block_service_test_observer.h"

namespace catsxp_shields {

AdBlockServiceTestObserver::AdBlockServiceTestObserver(
    AdBlockService* service) {
  observation_.Observe(service);
}

AdBlockServiceTestObserver::~AdBlockServiceTestObserver() = default;

void AdBlockServiceTestObserver::WaitForDefault() {
  default_loop_.Run();
}

void AdBlockServiceTestObserver::WaitForAdditional() {
  additional_loop_.Run();
}

void AdBlockServiceTestObserver::Wait(bool is_default_engine) {
  if (is_default_engine) {
    WaitForDefault();
  } else {
    WaitForAdditional();
  }
}

void AdBlockServiceTestObserver::OnFilterListLoaded(
    bool is_default_engine,
    AdBlockService::FilterListLoadResult result) {
  (is_default_engine ? default_loop_ : additional_loop_).Quit();
}

}  // namespace catsxp_shields
