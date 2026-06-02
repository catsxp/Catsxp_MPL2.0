/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_TEST_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_TEST_UTIL_H_

#include <string_view>
#include <vector>

#include "components/schema_org/common/metadata.mojom-forward.h"
#include "third_party/blink/public/mojom/document_metadata/document_metadata.mojom-forward.h"

namespace catsxp_ads::test {

std::vector<schema_org::mojom::EntityPtr>
CreativeSearchResultAdMojomWebPageEntities(
    std::vector<std::string_view> excluded_property_names);

blink::mojom::WebPagePtr CreativeSearchResultAdMojomWebPage(
    std::vector<std::string_view> excluded_property_names);

std::vector<schema_org::mojom::EntityPtr>
CreativeSearchResultAdMojomWebPageEntitiesWithProperty(std::string_view name,
                                                       std::string_view value);

blink::mojom::WebPagePtr CreativeSearchResultAdMojomWebPageWithProperty(
    std::string_view name,
    std::string_view value);

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_TEST_CREATIVE_SEARCH_RESULT_AD_MOJOM_WEB_PAGE_ENTITIES_TEST_UTIL_H_
