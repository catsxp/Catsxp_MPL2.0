/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_DELEGATE_H_

#include "base/time/time.h"

namespace catsxp_ads {

struct IssuersInfo;

class IssuersDelegate {
 public:
  // Invoked to tell the delegate we will fetch the issuers at `fetch_at`.
  virtual void OnWillFetchIssuers(base::Time fetch_at) {}

  // Invoked to tell the delegate we successfully fetched the `issuers`.
  virtual void OnDidFetchIssuers(const IssuersInfo& issuers) {}

  // Invoked to tell the delegate we failed to fetch the issuers.
  virtual void OnFailedToFetchIssuers() {}

  // Invoked to tell the delegate we will retry fetching the issuers at
  // `retry_at`.
  virtual void OnWillRetryFetchingIssuers(base::Time retry_at) {}

  // Invoked to tell the delegate we retried fetching the issuers.
  virtual void OnDidRetryFetchingIssuers() {}

 protected:
  virtual ~IssuersDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ACCOUNT_ISSUERS_ISSUERS_DELEGATE_H_
