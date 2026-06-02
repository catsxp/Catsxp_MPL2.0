/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/conversions/test/conversions_test_util.h"

#include "url/gurl.h"

namespace catsxp_ads::test {

// See `conversions_test_constants.h` for URL patterns that match and do not
// match.

std::vector<GURL> BuildDefaultConversionRedirectChain() {
  // Matches `kMatchingUrlPattern` and `kAnotherMatchingUrlPattern` in
  // `conversions_test_constants.h`.
  return {GURL("https://foo.com/bar"), GURL("https://qux.com/quux/corge")};
}

}  // namespace catsxp_ads::test
