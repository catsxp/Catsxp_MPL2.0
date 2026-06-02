/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_BAT_ADS_SERVICE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_BAT_ADS_SERVICE_H_

#include "base/functional/callback.h"
#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads.h"
#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_client_notifier.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace mojo {
template <typename T>
class PendingReceiver;
}  // namespace mojo

namespace catsxp_ads::test {

// Minimal in-process implementation of `bat_ads::mojom::BatAdsService`. Binds
// a `FakeBatAds` to the receiver from `Create` so `AdsServiceImpl` has a live
// mojo endpoint to send initialization messages to.
class FakeBatAdsService : public bat_ads::mojom::BatAdsService {
 public:
  FakeBatAdsService(base::RepeatingClosure initialize_callback,
                    base::RepeatingClosure shutdown_callback,
                    bool simulate_initialization_failure);

  FakeBatAdsService(const FakeBatAdsService&) = delete;
  FakeBatAdsService& operator=(const FakeBatAdsService&) = delete;

  ~FakeBatAdsService() override;

  void BindReceiver(mojo::PendingReceiver<bat_ads::mojom::BatAdsService>
                        bat_ads_service_pending_receiver);

  const FakeBatAdsClientNotifier* bat_ads_client_notifier() const {
    return &bat_ads_client_notifier_;
  }

  // bat_ads::mojom::BatAdsService:
  void Create(const base::FilePath& /*service_path*/,
              mojo::PendingAssociatedRemote<bat_ads::mojom::BatAdsClient>
              /*bat_ads_client_pending_associated_remote*/,
              mojo::PendingAssociatedReceiver<bat_ads::mojom::BatAds>
                  bat_ads_pending_associated_receiver,
              mojo::PendingReceiver<bat_ads::mojom::BatAdsClientNotifier>
                  bat_ads_client_notifier_pending_receiver,
              CreateCallback callback) override;

 private:
  base::RepeatingClosure shutdown_callback_;

  FakeBatAds bat_ads_;
  FakeBatAdsClientNotifier bat_ads_client_notifier_;
  mojo::Receiver<bat_ads::mojom::BatAdsService> bat_ads_service_receiver_{this};
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_BAT_ADS_SERVICE_H_
