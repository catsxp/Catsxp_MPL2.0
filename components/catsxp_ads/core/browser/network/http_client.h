/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_H_

#include <memory>
#include <optional>
#include <string>

#include "base/memory/raw_ref.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/buildflags/buildflags.h"
#include "catsxp/components/catsxp_ads/core/browser/network/http_client_callback.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "services/network/public/cpp/network_context_getter.h"
#include "url/gurl.h"

static_assert(BUILDFLAG(ENABLE_CATSXP_ADS));

class PrefService;

namespace network {
class SimpleURLLoader;
class SharedURLLoaderFactory;
}  // namespace network

namespace catsxp_ads {

class ObliviousHttpKeyConfig;

// Sends network requests, supporting both standard HTTP and Oblivious HTTP
// (OHTTP). Standard HTTP requests are issued via SimpleURLLoader, while OHTTP
// requests are routed through the network service’s OHTTP implementation.
class HttpClient final {
 public:
  HttpClient(PrefService& local_state,
             scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
             network::NetworkContextGetter network_context_getter,
             bool use_ohttp_staging);

  HttpClient(const HttpClient&) = delete;
  HttpClient& operator=(const HttpClient&) = delete;

  ~HttpClient();

  // Issues a network request described by `mojom::UrlRequestInfo`. When the
  // request completes, `callback` is invoked with a `mojom::UrlResponseInfo`.
  // The callback will not run if the request is canceled or if this instance
  // is destroyed.
  void SendRequest(mojom::UrlRequestInfoPtr mojom_url_request,
                   SendRequestCallback callback);

  // Cancels all active requests. Any pending callbacks will be dropped.
  void CancelRequests();

 private:
  // Sends the request using standard HTTP.
  void HttpRequest(mojom::UrlRequestInfoPtr mojom_url_request,
                   SendRequestCallback callback);
  void HttpRequestCallback(std::unique_ptr<network::SimpleURLLoader> url_loader,
                           SendRequestCallback callback,
                           std::optional<std::string> response_body);

  // Sends the request using Oblivious HTTP (OHTTP). For details, see
  // https://ietf-wg-ohai.github.io/oblivious-http/draft-ietf-ohai-ohttp.html
  void ObliviousHttpRequest(mojom::UrlRequestInfoPtr mojom_url_request,
                            const GURL& relay_url,
                            SendRequestCallback callback);
  void ObliviousHttpRequestCallback(
      SendRequestCallback callback,
      mojom::UrlResponseInfoPtr mojom_url_response);

  const raw_ref<PrefService> local_state_;

  const scoped_refptr<network::SharedURLLoaderFactory>
      url_loader_factory_;  // Not owned.

  const network::NetworkContextGetter network_context_getter_;

  const std::unique_ptr<ObliviousHttpKeyConfig> oblivious_http_key_config_;
  const GURL oblivious_http_relay_url_;

  base::WeakPtrFactory<HttpClient> weak_ptr_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_BROWSER_NETWORK_HTTP_CLIENT_H_
