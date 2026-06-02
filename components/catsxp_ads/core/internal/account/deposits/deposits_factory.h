/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_FACTORY_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_FACTORY_H_

#include <memory>

#include "catsxp/components/catsxp_ads/core/internal/account/deposits/deposit_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class DepositsFactory final {
 public:
  // This class contains only static methods.
  DepositsFactory() = delete;
  DepositsFactory(const DepositsFactory&) = delete;
  DepositsFactory& operator=(const DepositsFactory&) = delete;

  static std::unique_ptr<DepositInterface> Build(
      mojom::ConfirmationType mojom_confirmation_type);
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_FACTORY_H_
