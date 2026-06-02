/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INFO_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INFO_H_

#include <optional>
#include <string>

#include "base/time/time.h"

namespace catsxp_ads {

struct DepositInfo final {
  [[nodiscard]] bool IsValid() const;

  std::string creative_instance_id;
  double value = 0.0;
  std::optional<base::Time> expire_at;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INFO_H_
