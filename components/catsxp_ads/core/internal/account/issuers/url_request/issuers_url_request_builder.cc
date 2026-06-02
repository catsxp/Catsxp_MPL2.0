/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_builder.h"

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/issuers/url_request/issuers_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads {

namespace {

GURL BuildUrl() {
  const std::string spec =
      GetUrlHost(UrlHostType::kStatic) + BuildIssuersUrlPath();
  return GURL(spec);
}

}  // namespace

mojom::UrlRequestInfoPtr IssuersUrlRequestBuilder::Build() {
  mojom::UrlRequestInfoPtr mojom_url_request = mojom::UrlRequestInfo::New();
  mojom_url_request->url = BuildUrl();
  mojom_url_request->method = mojom::UrlRequestMethodType::kGet;

  return mojom_url_request;
}

}  // namespace catsxp_ads
