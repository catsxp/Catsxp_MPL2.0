/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/content/browser/creatives/search_result_ad/test/creative_search_result_ad_mojom_test_util.h"

namespace catsxp_ads::test {

schema_org::mojom::ValuesPtr CreateNewMojomValues(std::string value) {
  return schema_org::mojom::Values::NewStringValues({std::move(value)});
}

schema_org::mojom::ValuesPtr CreateNewMojomValues(int64_t value) {
  return schema_org::mojom::Values::NewLongValues({value});
}

}  // namespace catsxp_ads::test
