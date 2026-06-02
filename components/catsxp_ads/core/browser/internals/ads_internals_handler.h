/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/browser/service/ads_service_callback.h"
#include "catsxp/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "components/prefs/pref_change_registrar.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefService;

namespace catsxp_ads {
class AdsService;
}  // namespace catsxp_ads

class AdsInternalsHandler final : public bat_ads::mojom::AdsInternals {
 public:
  AdsInternalsHandler(catsxp_ads::AdsService* ads_service, PrefService& prefs);

  AdsInternalsHandler(const AdsInternalsHandler&) = delete;
  AdsInternalsHandler& operator=(const AdsInternalsHandler&) = delete;

  ~AdsInternalsHandler() override;

  void BindInterface(mojo::PendingReceiver<bat_ads::mojom::AdsInternals>
                         ads_internals_pending_receiver);

 private:
  // bat_ads::mojom::AdsInternals:
  void CreateAdsInternalsPageHandler(
      mojo::PendingRemote<bat_ads::mojom::AdsInternalsPage>
          ads_internals_page_pending_remote) override;
  void GetAdsInternals(GetAdsInternalsCallback callback) override;
  void ClearAdsData(catsxp_ads::ResultCallback callback) override;

  void GetInternalsCallback(GetAdsInternalsCallback callback,
                            std::optional<base::DictValue> dict);

  void OnCatsxpRewardsEnabledPrefChanged(const std::string& path);
  void UpdateCatsxpRewardsEnabled();

  const raw_ptr<catsxp_ads::AdsService> ads_service_;  // Not owned.

  const raw_ref<PrefService> prefs_;

  mojo::Receiver<bat_ads::mojom::AdsInternals> ads_internals_receiver_{this};

  mojo::Remote<bat_ads::mojom::AdsInternalsPage> ads_internals_page_remote_;

  PrefChangeRegistrar pref_change_registrar_;

  base::WeakPtrFactory<AdsInternalsHandler> weak_ptr_factory_{this};
};

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_INTERNALS_ADS_INTERNALS_HANDLER_H_
