/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_H_

#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmation_info.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/url_request_builder_interface.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

class GURL;

namespace catsxp_ads {

class FetchPaymentTokenUrlRequestBuilder final
    : public UrlRequestBuilderInterface {
 public:
  explicit FetchPaymentTokenUrlRequestBuilder(ConfirmationInfo confirmation);

  // UrlRequestBuilderInterface:
  mojom::UrlRequestInfoPtr Build() override;

 private:
  GURL BuildUrl() const;

  const ConfirmationInfo confirmation_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_UTILITY_REDEEM_CONFIRMATION_REWARD_URL_REQUEST_BUILDERS_FETCH_PAYMENT_TOKEN_URL_REQUEST_BUILDER_H_
