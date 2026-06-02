/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_TEST_ENVIRONMENT_TYPES_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_TEST_ENVIRONMENT_TYPES_TEST_UTIL_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::test {

std::string ToString(mojom::EnvironmentType mojom_environment_type);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMAND_LINE_SWITCHES_ENVIRONMENT_TEST_ENVIRONMENT_TYPES_TEST_UTIL_H_
