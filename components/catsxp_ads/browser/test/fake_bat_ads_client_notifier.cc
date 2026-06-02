/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads_client_notifier.h"

#include <ostream>
#include <utility>

#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace catsxp_ads::test {

FakeBatAdsClientNotifier::FakeBatAdsClientNotifier() = default;

FakeBatAdsClientNotifier::~FakeBatAdsClientNotifier() = default;

void FakeBatAdsClientNotifier::BindReceiver(
    mojo::PendingReceiver<bat_ads::mojom::BatAdsClientNotifier>
        pending_receiver) {
  receiver_.Bind(std::move(pending_receiver));
}

void FakeBatAdsClientNotifier::NotifyUserDidBecomeIdle() {
  ++become_idle_count_;
}

void FakeBatAdsClientNotifier::NotifyUserDidBecomeActive(
    base::TimeDelta idle_time,
    bool screen_was_locked) {
  ++become_active_count_;
  last_idle_time_ = idle_time;
  last_screen_was_locked_ = screen_was_locked;
}

}  // namespace catsxp_ads::test
