/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/get_signed_tokens_url_request_builder.h"

#include <utility>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/get_signed_tokens_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads {

GetSignedTokensUrlRequestBuilder::GetSignedTokensUrlRequestBuilder(
    WalletInfo wallet,
    std::string nonce)
    : wallet_(std::move(wallet)), nonce_(std::move(nonce)) {
  CHECK(wallet_.IsValid());
  CHECK(!nonce_.empty());
}

mojom::UrlRequestInfoPtr GetSignedTokensUrlRequestBuilder::Build() {
  mojom::UrlRequestInfoPtr mojom_url_request = mojom::UrlRequestInfo::New();
  mojom_url_request->url = BuildUrl();
  mojom_url_request->method = mojom::UrlRequestMethodType::kGet;

  return mojom_url_request;
}

///////////////////////////////////////////////////////////////////////////////

GURL GetSignedTokensUrlRequestBuilder::BuildUrl() const {
  const std::string spec =
      GetUrlHost(UrlHostType::kNonAnonymous) +
      BuildGetSignedTokensUrlPath(wallet_.payment_id, nonce_);
  return GURL(spec);
}

}  // namespace catsxp_ads
