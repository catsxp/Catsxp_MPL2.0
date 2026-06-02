/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/history/test/site_history_test_util.h"

namespace catsxp_ads::test {

SiteHistoryList BuildSiteHistory() {
  return {GURL("https://www.foobar.com"), GURL("https://www.foo.com"),
          GURL("https://www.bar.com"),    GURL("https://www.baz.com"),
          GURL("https://www.qux.com"),    GURL("https://www.quux.com"),
          GURL("https://www.corge.com"),  GURL("https://www.grault.com"),
          GURL("https://www.garply.com"), GURL("https://www.waldo.com"),
          GURL("https://www.fred.com"),   GURL("https://www.plugh.com"),
          GURL("https://www.xyzzy.com"),  GURL("https://www.thud.com")};
}

}  // namespace catsxp_ads::test
