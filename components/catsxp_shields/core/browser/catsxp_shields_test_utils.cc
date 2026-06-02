/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_shields/core/browser/catsxp_shields_test_utils.h"

namespace catsxp_shields {

// Declared in catsxp_shields_utils.cc.
extern uint32_t g_stable_farbling_tokens_seed;

ScopedStableFarblingTokensForTesting::ScopedStableFarblingTokensForTesting(
    uint32_t seed)
    : scoped_stable_farbling_token_seed_(&g_stable_farbling_tokens_seed, seed) {
}

ScopedStableFarblingTokensForTesting::~ScopedStableFarblingTokensForTesting() =
    default;

}  // namespace catsxp_shields
