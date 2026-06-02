/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/public/ads.h"

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_impl.h"

namespace catsxp_ads {

// static
std::unique_ptr<Ads> Ads::CreateInstance(AdsClient& ads_client,
                                         const base::FilePath& database_path) {
  return std::make_unique<AdsImpl>(ads_client, database_path,
                                   std::make_unique<TokenGenerator>());
}

}  // namespace catsxp_ads
