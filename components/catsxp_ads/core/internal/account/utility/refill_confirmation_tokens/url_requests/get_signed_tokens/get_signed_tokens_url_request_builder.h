/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {

class GetSignedTokensUrlRequestBuilder final
    : public UrlRequestBuilderInterface {
 public:
  GetSignedTokensUrlRequestBuilder(WalletInfo wallet, std::string nonce);

  // UrlRequestBuilderInterface:
  mojom::UrlRequestInfoPtr Build() override;

 private:
  GURL BuildUrl() const;

  const WalletInfo wallet_;

  const std::string nonce_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_GET_SIGNED_TOKENS_GET_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
