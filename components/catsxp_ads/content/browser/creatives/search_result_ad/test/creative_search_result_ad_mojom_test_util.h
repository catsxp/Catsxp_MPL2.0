/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_TEST_UTIL_H_

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "components/schema_org/common/metadata.mojom.h"

namespace catsxp_ads::test {

schema_org::mojom::ValuesPtr CreateNewMojomValues(std::string value);

schema_org::mojom::ValuesPtr CreateNewMojomValues(int64_t value);

template <typename T>
void AddMojomProperty(
    std::vector<schema_org::mojom::PropertyPtr>* mojom_properties,
    const std::string& name,
    T value) {
  CHECK(mojom_properties);

  schema_org::mojom::PropertyPtr mojom_property =
      schema_org::mojom::Property::New();

  mojom_property->name = name;

  static_assert(!std::is_same_v<T, bool>,
                "There are no bool overrides for CreateNewMojomValues in the "
                "overloads above");
  mojom_property->values = CreateNewMojomValues(value);

  mojom_properties->push_back(std::move(mojom_property));
}

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_TEST_UTIL_H_
