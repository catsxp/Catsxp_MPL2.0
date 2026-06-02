/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_bat_ads.h"

#include <optional>
#include <ostream>
#include <utility>

#include "base/time/time.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"

namespace catsxp_ads::test {

FakeBatAds::FakeBatAds(base::RepeatingClosure initialize_callback,
                       bool simulate_initialization_failure)
    : initialize_callback_(std::move(initialize_callback)),
      simulate_initialization_failure_(simulate_initialization_failure) {}

FakeBatAds::~FakeBatAds() = default;

void FakeBatAds::BindReceiver(
    mojo::PendingAssociatedReceiver<bat_ads::mojom::BatAds>
        bat_ads_pending_associated_receiver) {
  bat_ads_associated_receiver_.Bind(
      std::move(bat_ads_pending_associated_receiver));
}

void FakeBatAds::Initialize(catsxp_ads::mojom::WalletInfoPtr /*mojom_wallet*/,
                            InitializeCallback callback) {
  if (!simulate_initialization_failure_) {
    initialize_callback_.Run();
  }
  std::move(callback).Run(!simulate_initialization_failure_);
}

void FakeBatAds::Shutdown(ShutdownCallback callback) {
  std::move(callback).Run(/*success=*/true);
}

void FakeBatAds::GetInternals(GetInternalsCallback callback) {
  std::move(callback).Run(/*value=*/std::nullopt);
}

void FakeBatAds::GetDiagnostics(GetDiagnosticsCallback callback) {
  std::move(callback).Run(/*value=*/std::nullopt);
}

void FakeBatAds::GetStatementOfAccounts(
    GetStatementOfAccountsCallback callback) {
  std::move(callback).Run(/*mojom_statement=*/nullptr);
}

void FakeBatAds::ParseAndSaveNewTabPageAds(
    base::DictValue /*value*/,
    ParseAndSaveNewTabPageAdsCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::MaybeServeNewTabPageAd(
    MaybeServeNewTabPageAdCallback callback) {
  std::move(callback).Run(/*value=*/nullptr);
}

void FakeBatAds::TriggerNewTabPageAdEvent(
    const std::string& /*placement_id*/,
    const std::string& /*creative_instance_id*/,
    catsxp_ads::mojom::NewTabPageAdMetricType /*mojom_ad_metric_type*/,
    catsxp_ads::mojom::NewTabPageAdEventType /*mojom_ad_event_type*/,
    TriggerNewTabPageAdEventCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::MaybeGetNotificationAd(
    const std::string& /*placement_id*/,
    MaybeGetNotificationAdCallback callback) {
  std::move(callback).Run(/*value=*/std::nullopt);
}

void FakeBatAds::TriggerNotificationAdEvent(
    const std::string& /*placement_id*/,
    catsxp_ads::mojom::NotificationAdEventType /*mojom_ad_event_type*/,
    TriggerNotificationAdEventCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::MaybeGetSearchResultAd(
    const std::string& /*placement_id*/,
    MaybeGetSearchResultAdCallback callback) {
  std::move(callback).Run(/*search_result_ad=*/nullptr);
}

void FakeBatAds::TriggerSearchResultAdEvent(
    catsxp_ads::mojom::CreativeSearchResultAdInfoPtr /*mojom_creative_ad*/,
    catsxp_ads::mojom::SearchResultAdEventType /*mojom_ad_event_type*/,
    TriggerSearchResultAdEventCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::PurgeOrphanedAdEventsForType(
    catsxp_ads::mojom::AdType /*mojom_ad_type*/,
    PurgeOrphanedAdEventsForTypeCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::GetAdHistory(base::Time /*from_time*/,
                              base::Time /*to_time*/,
                              GetAdHistoryCallback callback) {
  std::move(callback).Run(/*value=*/std::nullopt);
}

void FakeBatAds::ToggleLikeAd(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleLikeAdCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::ToggleDislikeAd(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleDislikeAdCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::ToggleLikeSegment(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleLikeSegmentCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::ToggleDislikeSegment(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleDislikeSegmentCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::ToggleSaveAd(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleSaveAdCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

void FakeBatAds::ToggleMarkAdAsInappropriate(
    catsxp_ads::mojom::ReactionInfoPtr /*mojom_reaction*/,
    ToggleMarkAdAsInappropriateCallback callback) {
  std::move(callback).Run(/*success=*/false);
}

}  // namespace catsxp_ads::test
