/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_service.h"

#include <ostream>
#include <utility>

#include "base/functional/callback.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace catsxp_ads::test {

FakeBatAdsService::FakeBatAdsService(base::RepeatingClosure initialize_callback,
                                     base::RepeatingClosure shutdown_callback,
                                     bool simulate_initialization_failure)
    : shutdown_callback_(std::move(shutdown_callback)),
      bat_ads_(std::move(initialize_callback),
               simulate_initialization_failure) {}

FakeBatAdsService::~FakeBatAdsService() = default;

void FakeBatAdsService::BindReceiver(
    mojo::PendingReceiver<bat_ads::mojom::BatAdsService>
        bat_ads_service_pending_receiver) {
  bat_ads_service_receiver_.Bind(std::move(bat_ads_service_pending_receiver));
  // Notify the factory when `AdsServiceImpl` closes its end of the pipe so
  // tests can wait for the full shutdown sequence to complete.
  bat_ads_service_receiver_.set_disconnect_handler(shutdown_callback_);
}

void FakeBatAdsService::Create(
    const base::FilePath& /*service_path*/,
    mojo::PendingAssociatedRemote<bat_ads::mojom::BatAdsClient>
    /*bat_ads_client_pending_associated_remote*/,
    mojo::PendingAssociatedReceiver<bat_ads::mojom::BatAds>
        bat_ads_pending_associated_receiver,
    mojo::PendingReceiver<bat_ads::mojom::BatAdsClientNotifier>
        bat_ads_client_notifier_pending_receiver,
    CreateCallback callback) {
  bat_ads_.BindReceiver(std::move(bat_ads_pending_associated_receiver));
  bat_ads_client_notifier_.BindReceiver(
      std::move(bat_ads_client_notifier_pending_receiver));
  std::move(callback).Run();
}

}  // namespace catsxp_ads::test
