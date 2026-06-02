/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_UNIT_TEST_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_UNIT_TEST_HELPER_H_

namespace catsxp_shields {

class AdBlockService;

// Simulates an empty filter list catalog load, which unblocks the component
// provider gates that guard initial filter set loading. Tests that do not
// install the real catalog component must call this before any filter set
// loading is expected to succeed.
void SetupAdBlockServiceForTesting(AdBlockService* ad_block_service);

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_TEST_AD_BLOCK_UNIT_TEST_HELPER_H_
