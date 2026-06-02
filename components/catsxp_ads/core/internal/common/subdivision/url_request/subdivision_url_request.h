/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_H_

#include <string>

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

class SubdivisionUrlRequest final {
 public:
  SubdivisionUrlRequest();

  SubdivisionUrlRequest(const SubdivisionUrlRequest&) = delete;
  SubdivisionUrlRequest& operator=(const SubdivisionUrlRequest&) = delete;

  ~SubdivisionUrlRequest();

  void SetDelegate(SubdivisionUrlRequestDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void PeriodicallyFetch();

 private:
  void Fetch();
  void FetchCallback(const mojom::UrlResponseInfo& mojom_url_response);
  void FetchAfterDelay();

  void SuccessfullyFetchedSubdivision(const std::string& subdivision);
  void FailedToFetchSubdivision(bool should_retry);

  void Retry();
  void RetryCallback();
  void StopRetrying();

  void NotifyWillFetchSubdivision(base::Time fetch_at) const;
  void NotifyDidFetchSubdivision(const std::string& subdivision) const;
  void NotifyFailedToFetchSubdivision() const;
  void NotifyWillRetryFetchingSubdivision(base::Time retry_at) const;
  void NotifyDidRetryFetchingSubdivision() const;

  raw_ptr<SubdivisionUrlRequestDelegate> delegate_ = nullptr;  // Not owned.

  bool is_periodically_fetching_ = false;

  bool is_fetching_ = false;

  BackoffTimer timer_;

  base::WeakPtrFactory<SubdivisionUrlRequest> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_H_
