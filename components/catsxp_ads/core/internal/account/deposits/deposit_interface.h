/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_

#include <string>

#include "base/functional/callback.h"

namespace catsxp_ads {

using GetDepositCallback = base::OnceCallback<void(bool success, double value)>;

class DepositInterface {
 public:
  virtual ~DepositInterface() = default;

  // Returns the deposit value for the given `creative_instance_id`.
  virtual void GetValue(const std::string& creative_instance_id,
                        GetDepositCallback callback) = 0;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_
