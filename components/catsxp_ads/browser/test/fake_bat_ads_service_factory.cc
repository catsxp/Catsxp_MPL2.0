/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_service_factory.h"

#include <memory>
#include <ostream>

#include "base/functional/bind.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_client_notifier.h"
#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_service.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace catsxp_ads::test {

FakeBatAdsServiceFactory::FakeBatAdsServiceFactory() = default;

FakeBatAdsServiceFactory::~FakeBatAdsServiceFactory() = default;

const FakeBatAdsClientNotifier*
FakeBatAdsServiceFactory::bat_ads_client_notifier() const {
  return bat_ads_service_ ? bat_ads_service_->bat_ads_client_notifier()
                          : nullptr;
}

size_t FakeBatAdsServiceFactory::become_idle_count() const {
  const FakeBatAdsClientNotifier* const notifier = bat_ads_client_notifier();
  return notifier ? notifier->become_idle_count() : 0U;
}

size_t FakeBatAdsServiceFactory::become_active_count() const {
  const FakeBatAdsClientNotifier* const notifier = bat_ads_client_notifier();
  return notifier ? notifier->become_active_count() : 0U;
}

base::TimeDelta FakeBatAdsServiceFactory::last_idle_time() const {
  const FakeBatAdsClientNotifier* const notifier = bat_ads_client_notifier();
  return notifier ? notifier->last_idle_time() : base::TimeDelta{};
}

bool FakeBatAdsServiceFactory::last_screen_was_locked() const {
  const FakeBatAdsClientNotifier* const notifier = bat_ads_client_notifier();
  return notifier ? notifier->last_screen_was_locked() : false;
}

mojo::Remote<bat_ads::mojom::BatAdsService> FakeBatAdsServiceFactory::Launch()
    const {
  ++launch_count_;

  mojo::Remote<bat_ads::mojom::BatAdsService> bat_ads_service_remote;

  bat_ads_service_ = std::make_unique<FakeBatAdsService>(
      base::BindRepeating(&FakeBatAdsServiceFactory::OnInitialize,
                          base::Unretained(this)),
      base::BindRepeating(&FakeBatAdsServiceFactory::OnShutdown,
                          base::Unretained(this)),
      simulate_initialization_failure_);
  bat_ads_service_->BindReceiver(
      bat_ads_service_remote.BindNewPipeAndPassReceiver());

  return bat_ads_service_remote;
}

}  // namespace catsxp_ads::test
