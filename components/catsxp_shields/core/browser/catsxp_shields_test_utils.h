/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_TEST_UTILS_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_TEST_UTILS_H_

#include <stdint.h>

#include "base/auto_reset.h"

namespace catsxp_shields {

class ScopedStableFarblingTokensForTesting {
 public:
  // The seed value determines whether the farbling is random or deterministic.
  // If the seed is 0, the farbling is random (production mode). If the seed is
  // non-zero, the farbling is deterministic.
  explicit ScopedStableFarblingTokensForTesting(uint32_t seed);
  ~ScopedStableFarblingTokensForTesting();

 private:
  base::AutoReset<uint32_t> scoped_stable_farbling_token_seed_;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CORE_BROWSER_CATSXP_SHIELDS_TEST_UTILS_H_
