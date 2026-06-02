/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_

#include <string>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/challenge_bypass_ristretto/blinded_token.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {

class RequestSignedTokensUrlRequestBuilder final
    : public UrlRequestBuilderInterface {
 public:
  RequestSignedTokensUrlRequestBuilder(WalletInfo wallet,
                                       cbr::BlindedTokenList tokens);

  RequestSignedTokensUrlRequestBuilder(
      const RequestSignedTokensUrlRequestBuilder&) = delete;
  RequestSignedTokensUrlRequestBuilder& operator=(
      const RequestSignedTokensUrlRequestBuilder&) = delete;

  ~RequestSignedTokensUrlRequestBuilder() override;

  // UrlRequestBuilderInterface:
  mojom::UrlRequestInfoPtr Build() override;

 private:
  GURL BuildUrl() const;

  std::vector<std::string> BuildHeaders(const std::string& body) const;
  std::string BuildSignatureHeaderValue(const std::string& body) const;

  std::string BuildBody() const;

  const WalletInfo wallet_;
  const cbr::BlindedTokenList blinded_tokens_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REFILL_CONFIRMATION_TOKENS_URL_REQUESTS_REQUEST_SIGNED_TOKENS_REQUEST_SIGNED_TOKENS_URL_REQUEST_BUILDER_H_
