/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/user_data_builder/fixed/confirmation_fixed_user_data_builder.h"

#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/build_channel_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/catalog_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/country_code_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/created_at_timestamp_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/platform_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/rotating_hash_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/segment_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/studies_user_data.h"
#include "catsxp/components/catsxp_ads/core/internal/account/user_data/fixed/version_number_user_data.h"

namespace catsxp_ads {

base::DictValue BuildFixedUserData(const TransactionInfo& transaction) {
  base::DictValue user_data;

  user_data.Merge(BuildBuildChannelUserData());
  user_data.Merge(BuildCatalogUserData());
  user_data.Merge(BuildCountryCodeUserData());
  user_data.Merge(BuildCreatedAtTimestampUserData(transaction));
  user_data.Merge(BuildPlatformUserData());
  user_data.Merge(BuildRotatingHashUserData(transaction));
  user_data.Merge(BuildSegmentUserData(transaction));
  user_data.Merge(BuildStudiesUserData());
  user_data.Merge(BuildVersionNumberUserData());

  return user_data;
}

}  // namespace catsxp_ads
