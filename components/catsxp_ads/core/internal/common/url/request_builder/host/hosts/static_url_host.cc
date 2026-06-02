/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/static_url_host.h"

#include "catsxp/components/catsxp_ads/core/internal/global_state/global_state.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr char kProductionHost[] = "https://static.ads.catsxp.com";
constexpr char kStagingHost[] = "https://static.ads.catsxpsoftware.com";

}  // namespace

std::string StaticUrlHost::Get() const {
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
