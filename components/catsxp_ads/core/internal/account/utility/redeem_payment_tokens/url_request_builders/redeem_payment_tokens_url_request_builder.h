/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDERS_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDERS_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDER_H_

#include <string>

#include "base/values.h"
#include "catsxp/components/catsxp_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "catsxp/components/catsxp_ads/core/internal/account/wallet/wallet_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {

class RedeemPaymentTokensUrlRequestBuilder final
    : public UrlRequestBuilderInterface {
 public:
  RedeemPaymentTokensUrlRequestBuilder(WalletInfo wallet,
                                       PaymentTokenList payment_tokens,
                                       base::DictValue user_data);

  RedeemPaymentTokensUrlRequestBuilder(
      const RedeemPaymentTokensUrlRequestBuilder&) = delete;
  RedeemPaymentTokensUrlRequestBuilder& operator=(
      const RedeemPaymentTokensUrlRequestBuilder&) = delete;

  ~RedeemPaymentTokensUrlRequestBuilder() override;

  // UrlRequestBuilderInterface:
  mojom::UrlRequestInfoPtr Build() override;

 private:
  GURL BuildUrl() const;

  std::string BuildBody(const std::string& payload);

  std::string BuildPayload() const;

  base::ListValue BuildPaymentRequestDTO(const std::string& payload) const;

  const WalletInfo wallet_;
  const PaymentTokenList payment_tokens_;
  base::DictValue user_data_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDERS_REDEEM_PAYMENT_TOKENS_URL_REQUEST_BUILDER_H_
