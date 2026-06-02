/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/geo_url_host.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr char kProductionHost[] = "https://geo.ads.catsxp.com";
constexpr char kStagingHost[] = "https://geo.ads.catsxpsoftware.com";

}  // namespace

std::string GeoUrlHost::Get() const {
  const mojom::EnvironmentType mojom_environment_type =
      GlobalState::GetInstance()->CommandLineSwitches().environment_type;

  switch (mojom_environment_type) {
    case mojom::EnvironmentType::kProduction: {
      return kProductionHost;
    }

    case mojom::EnvironmentType::kStaging: {
      return kStagingHost;
    }
  }
}

}  // namespace catsxp_ads
