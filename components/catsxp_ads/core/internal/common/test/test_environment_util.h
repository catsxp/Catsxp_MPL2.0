/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TEST_ENVIRONMENT_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TEST_ENVIRONMENT_UTIL_H_

#include "catsxp/components/catsxp_ads/core/internal/common/test/build_channel_test_types.h"

// Helpers for configuring global test environment state including device
// identity, build channel, content settings, and platform.

namespace catsxp_ads::test {

void SetUpDeviceId();

void SetUpBuildChannel(BuildChannelType type);

void SetUpAllowJavaScript(bool allow_javascript);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_TEST_TEST_ENVIRONMENT_UTIL_H_
