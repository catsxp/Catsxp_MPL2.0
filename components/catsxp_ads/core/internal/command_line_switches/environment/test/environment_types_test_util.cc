/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/command_line_switches/environment/test/environment_types_test_util.h"

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads::test {

namespace {

constexpr char kProductionEnvironment[] = "Production";
constexpr char kStagingEnvironment[] = "Staging";

}  // namespace

std::string ToString(mojom::EnvironmentType mojom_environment_type) {
  switch (mojom_environment_type) {
    case mojom::EnvironmentType::kProduction: {
      return kProductionEnvironment;
    }

    case mojom::EnvironmentType::kStaging: {
      return kStagingEnvironment;
    }
  }
}

}  // namespace catsxp_ads::test
