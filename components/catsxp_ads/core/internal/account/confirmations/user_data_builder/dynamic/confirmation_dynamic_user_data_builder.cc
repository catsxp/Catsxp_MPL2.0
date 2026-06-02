/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/dynamic/confirmation_dynamic_user_data_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/diagnostic_id_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/dynamic/system_timestamp_user_data.h"

namespace catsxp_ads {

base::DictValue BuildDynamicUserData() {
  base::DictValue user_data;

  user_data.Merge(BuildDiagnosticIdUserData());
  user_data.Merge(BuildSystemTimestampUserData());

  return user_data;
}

}  // namespace catsxp_ads
