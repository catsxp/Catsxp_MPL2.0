/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_H_

#include "base/check_op.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/internal/account/issuers/issuers_delegate.h"
#include "catsxp/components/catsxp_ads/core/internal/common/timer/backoff_timer.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"

namespace catsxp_ads {

struct IssuersInfo;

class Issuers final {
 public:
  Issuers();

  Issuers(const Issuers&) = delete;
  Issuers& operator=(const Issuers&) = delete;

  ~Issuers();

  void SetDelegate(IssuersDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void PeriodicallyFetch();

 private:
  void Fetch();
  void FetchCallback(const mojom::UrlResponseInfo& mojom_url_response);
  void FetchAfterDelay();

  void SuccessfullyFetchedIssuers(const IssuersInfo& issuers);
  void FailedToFetchIssuers(bool should_retry);

  void Retry();
  void RetryCallback();
  void StopRetrying();

  void NotifyDidFetchIssuers(const IssuersInfo& issuers) const;
  void NotifyFailedToFetchIssuers() const;
  void NotifyWillFetchIssuers(base::Time fetch_at) const;
  void NotifyWillRetryFetchingIssuers(base::Time retry_at) const;
  void NotifyDidRetryFetchingIssuers() const;

  raw_ptr<IssuersDelegate> delegate_ = nullptr;  // Not owned.

  bool is_periodically_fetching_ = false;

  bool is_fetching_ = false;

  BackoffTimer timer_;

  base::WeakPtrFactory<Issuers> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_H_
