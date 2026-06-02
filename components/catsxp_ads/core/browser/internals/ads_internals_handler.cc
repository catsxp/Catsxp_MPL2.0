/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/internals/ads_internals_handler.h"

#include <utility>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/json/json_writer.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"
#include "catsxp/components/catsxp_rewards/core/pref_names.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "components/prefs/pref_service.h"

AdsInternalsHandler::AdsInternalsHandler(catsxp_ads::AdsService* ads_service,
                                         PrefService& prefs)
    : ads_service_(ads_service), prefs_(prefs) {
  pref_change_registrar_.Init(&*prefs_);
  pref_change_registrar_.Add(
      catsxp_rewards::prefs::kEnabled,
      base::BindRepeating(
          &AdsInternalsHandler::OnCatsxpRewardsEnabledPrefChanged,
          weak_ptr_factory_.GetWeakPtr()));
}

AdsInternalsHandler::~AdsInternalsHandler() = default;

void AdsInternalsHandler::BindInterface(
    mojo::PendingReceiver<bat_ads::mojom::AdsInternals>
        ads_internals_pending_receiver) {
  if (ads_internals_receiver_.is_bound()) {
    ads_internals_receiver_.reset();
  }

  ads_internals_receiver_.Bind(std::move(ads_internals_pending_receiver));
}

///////////////////////////////////////////////////////////////////////////////

void AdsInternalsHandler::CreateAdsInternalsPageHandler(
    mojo::PendingRemote<bat_ads::mojom::AdsInternalsPage>
        ads_internals_page_pending_remote) {
  ads_internals_page_remote_ = mojo::Remote<bat_ads::mojom::AdsInternalsPage>(
      std::move(ads_internals_page_pending_remote));

  UpdateCatsxpRewardsEnabled();
}

void AdsInternalsHandler::GetAdsInternals(GetAdsInternalsCallback callback) {
  if (!ads_service_) {
    return std::move(callback).Run(/*ads_internals=*/"{}");
  }

  ads_service_->GetInternals(
      base::BindOnce(&AdsInternalsHandler::GetInternalsCallback,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
}

void AdsInternalsHandler::ClearAdsData(catsxp_ads::ResultCallback callback) {
  if (!ads_service_) {
    return std::move(callback).Run(/*success=*/false);
  }

  ads_service_->ClearData(std::move(callback));
}

void AdsInternalsHandler::GetInternalsCallback(
    GetAdsInternalsCallback callback,
    std::optional<base::DictValue> dict) {
  // `dict` can be nullopt in the following cases:
  // - `bat_ads::mojom::BatAds` associated remote is not bound.
  // - A database query fails.
  std::string json;
  CHECK(base::JSONWriter::Write(std::move(dict).value_or(base::DictValue{}),
                                &json));
  std::move(callback).Run(json);
}

void AdsInternalsHandler::OnCatsxpRewardsEnabledPrefChanged(
    const std::string& /*path*/) {
  UpdateCatsxpRewardsEnabled();
}

void AdsInternalsHandler::UpdateCatsxpRewardsEnabled() {
  if (!ads_internals_page_remote_) {
    return;
  }

  const bool is_enabled = prefs_->GetBoolean(catsxp_rewards::prefs::kEnabled);
  ads_internals_page_remote_->UpdateCatsxpRewardsEnabled(is_enabled);
}
