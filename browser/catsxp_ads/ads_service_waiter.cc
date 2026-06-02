/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/ads_service_waiter.h"

#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"

namespace catsxp_ads::test {

AdsServiceWaiter::AdsServiceWaiter(AdsService& ads_service)
    : ads_service_(ads_service) {
  observation_.Observe(&ads_service);
}

AdsServiceWaiter::~AdsServiceWaiter() = default;

void AdsServiceWaiter::WaitForOnAdsServiceIneligibleToStart() {
  // `OnAdsServiceIneligibleToStart` will not fire again if the service was
  // marked ineligible before observation began.
  if (!ads_service_->IsIneligibleToStart()) {
    on_ads_service_ineligible_to_start_run_loop_.Run();
  }
}

void AdsServiceWaiter::WaitForOnDidInitializeAdsService() {
  // `OnDidInitializeAdsService` will not fire again if the service was already
  // initialized before observation began.
  if (!ads_service_->IsInitialized()) {
    on_did_initialize_ads_service_run_loop_.Run();
  }
}

void AdsServiceWaiter::WaitForOnDidShutdownAdsService() {
  on_did_shutdown_ads_service_run_loop_.Run();
}

void AdsServiceWaiter::WaitForOnDidClearAdsServiceData() {
  on_did_clear_ads_service_data_run_loop_.Run();
}

///////////////////////////////////////////////////////////////////////////////

void AdsServiceWaiter::OnAdsServiceIneligibleToStart() {
  on_ads_service_ineligible_to_start_run_loop_.Quit();
}

void AdsServiceWaiter::OnDidInitializeAdsService() {
  on_did_initialize_ads_service_run_loop_.Quit();
}

void AdsServiceWaiter::OnDidShutdownAdsService() {
  on_did_shutdown_ads_service_run_loop_.Quit();
}

void AdsServiceWaiter::OnDidClearAdsServiceData() {
  on_did_clear_ads_service_data_run_loop_.Quit();
}

}  // namespace catsxp_ads::test
