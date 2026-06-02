/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/legacy_migration/legacy_migration_util.h"

#include <string>

#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

void MaybeDeleteFile(const std::string& name) {
  GetAdsClient().Remove(name,
                        base::BindOnce(
                            [](const std::string& filename, bool success) {
                              if (!success) {
                                BLOG(0, "Failed to delete " << filename);
                              }
                            },
                            name));
}

}  // namespace catsxp_ads
