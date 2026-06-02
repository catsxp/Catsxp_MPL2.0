/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/fetch_payment_token_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads {

FetchPaymentTokenUrlRequestBuilder::FetchPaymentTokenUrlRequestBuilder(
    ConfirmationInfo confirmation)
    : confirmation_(std::move(confirmation)) {
  CHECK(IsValid(confirmation_));
}

mojom::UrlRequestInfoPtr FetchPaymentTokenUrlRequestBuilder::Build() {
  mojom::UrlRequestInfoPtr mojom_url_request = mojom::UrlRequestInfo::New();
  mojom_url_request->url = BuildUrl();
  mojom_url_request->method = mojom::UrlRequestMethodType::kGet;

  return mojom_url_request;
}

///////////////////////////////////////////////////////////////////////////////

GURL FetchPaymentTokenUrlRequestBuilder::BuildUrl() const {
  const std::string url_host =
      confirmation_.ad_type == mojom::AdType::kSearchResultAd
          ? GetUrlHost(UrlHostType::kAnonymousSearch)
          : GetUrlHost(UrlHostType::kAnonymous);

  const std::string spec =
      url_host + BuildFetchPaymentTokenUrlPath(confirmation_.transaction_id);

  return GURL(spec);
}

}  // namespace catsxp_ads
