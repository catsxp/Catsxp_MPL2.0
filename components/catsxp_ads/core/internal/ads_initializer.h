/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_INITIALIZER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_INITIALIZER_H_

#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "catsxp/components/catsxp_ads/core/public/ads_callback.h"

namespace catsxp_ads {

// Runs the multi-step initialization pipeline (database open, client state
// migration and load, confirmation state migration and load) and signals
// completion via `ResultCallback`.
class AdsInitializer {
 public:
  AdsInitializer();

  AdsInitializer(const AdsInitializer&) = delete;
  AdsInitializer& operator=(const AdsInitializer&) = delete;

  ~AdsInitializer();

  void Initialize(mojom::WalletInfoPtr wallet, ResultCallback callback);

 private:
  void CreateOrOpenDatabase(mojom::WalletInfoPtr wallet,
                            ResultCallback callback);
  void CreateOrOpenDatabaseCallback(mojom::WalletInfoPtr wallet,
                                    ResultCallback callback,
                                    bool success);

  void MigrateClientStateCallback(mojom::WalletInfoPtr wallet,
                                  ResultCallback callback,
                                  bool success);
  void LoadClientStateCallback(mojom::WalletInfoPtr wallet,
                               ResultCallback callback,
                               bool success);
  void MigrateConfirmationStateCallback(mojom::WalletInfoPtr wallet,
                                        ResultCallback callback,
                                        bool success);
  void LoadConfirmationStateCallback(mojom::WalletInfoPtr wallet,
                                     ResultCallback callback,
                                     bool success);

  void SuccessfullyInitialized(mojom::WalletInfoPtr wallet,
                               ResultCallback callback);

  base::WeakPtrFactory<AdsInitializer> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_INITIALIZER_H_
