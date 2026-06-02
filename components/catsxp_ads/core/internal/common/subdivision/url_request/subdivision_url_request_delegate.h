/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_DELEGATE_H_

#include <string>

#include "base/time/time.h"

namespace catsxp_ads {

class SubdivisionUrlRequestDelegate {
 public:
  // Invoked to tell the delegate we will fetch the subdivision at `fetch_at`.
  virtual void OnWillFetchSubdivision(base::Time fetch_at) {}

  // Invoked to tell the delegate we successfully fetched the `subdivision`.
  virtual void OnDidFetchSubdivision(const std::string& subdvision) {}

  // Invoked to tell the delegate we failed to fetch the subdivision.
  virtual void OnFailedToFetchSubdivision() {}

  // Invoked to tell the delegate we will retry fetching the subdivision at
  // `retry_at`.
  virtual void OnWillRetryFetchingSubdivision(base::Time retry_at) {}

  // Invoked to tell the delegate we retried fetching the subdivision.
  virtual void OnDidRetryFetchingSubdivision() {}

 protected:
  virtual ~SubdivisionUrlRequestDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_URL_REQUEST_SUBDIVISION_URL_REQUEST_DELEGATE_H_
