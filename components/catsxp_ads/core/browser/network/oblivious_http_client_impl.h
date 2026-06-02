/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CLIENT_IMPL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CLIENT_IMPL_H_

#include "catsxp/components/catsxp_ads/core/browser/network/http_client_callback.h"
#include "services/network/public/mojom/oblivious_http_request.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads {

class ObliviousHttpClientImpl final
    : public network::mojom::ObliviousHttpClient {
 public:
  ObliviousHttpClientImpl(GURL url, SendRequestCallback callback);

  ObliviousHttpClientImpl(const ObliviousHttpClientImpl&) = delete;
  ObliviousHttpClientImpl& operator=(const ObliviousHttpClientImpl&) = delete;

  ~ObliviousHttpClientImpl() override;

  // network::mojom::ObliviousHttpClient:
  void OnCompleted(
      network::mojom::ObliviousHttpCompletionResultPtr response) override;

 private:
  const GURL url_;
  SendRequestCallback callback_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_OBLIVIOUS_HTTP_CLIENT_IMPL_H_
