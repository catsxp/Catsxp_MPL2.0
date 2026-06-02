/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATION_TYPE_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATION_TYPE_TEST_UTIL_H_

#include <cstddef>
#include <vector>

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads::test {

std::vector<mojom::ConfirmationType>
BuildConfirmationTypeForCountAndIntersperseOtherTypes(
    mojom::ConfirmationType mojom_confirmation_type,
    size_t count);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_TEST_CONFIRMATION_TYPE_TEST_UTIL_H_
