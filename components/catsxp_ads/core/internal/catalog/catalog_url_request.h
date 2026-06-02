/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_H_

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/catalog/catalog_url_request_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct CatalogInfo;

class CatalogUrlRequest final {
 public:
  CatalogUrlRequest();

  CatalogUrlRequest(const CatalogUrlRequest&) = delete;
  CatalogUrlRequest& operator=(const CatalogUrlRequest&) = delete;

  ~CatalogUrlRequest();

  void SetDelegate(CatalogUrlRequestDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void PeriodicallyFetch();

 private:
  void Fetch();
  void FetchCallback(const mojom::UrlResponseInfo& mojom_url_response);
  void FetchAfterDelay();

  void SuccessfullyFetchedCatalog(const CatalogInfo& catalog);
  void FailedToFetchCatalog(bool should_retry);

  void Retry();
  void RetryCallback();
  void StopRetrying();

  void NotifyWillFetchCatalog(base::Time fetch_at) const;
  void NotifyDidFetchCatalog(const CatalogInfo& catalog) const;
  void NotifyFailedToFetchCatalog() const;
  void NotifyWillRetryFetchingCatalog(base::Time retry_at) const;
  void NotifyDidRetryFetchingCatalog() const;

  raw_ptr<CatalogUrlRequestDelegate> delegate_ = nullptr;  // Not owned.

  bool is_periodically_fetching_ = false;

  bool is_fetching_ = false;

  BackoffTimer timer_;

  base::WeakPtrFactory<CatalogUrlRequest> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_CATALOG_CATALOG_URL_REQUEST_H_
