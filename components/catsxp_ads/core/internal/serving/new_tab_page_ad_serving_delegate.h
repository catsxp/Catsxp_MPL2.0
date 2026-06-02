/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_H_

namespace catsxp_ads {

struct NewTabPageAdInfo;

class NewTabPageAdServingDelegate {
 public:
  // Invoked when an opportunity arises to serve a new tab page ad.
  virtual void OnOpportunityAroseToServeNewTabPageAd() {}

  // Invoked when a new tab page ad is served.
  virtual void OnDidServeNewTabPageAd(const NewTabPageAdInfo& ad) {}

  // Invoked when a new tab page ad fails to serve.
  virtual void OnFailedToServeNewTabPageAd() {}

 protected:
  virtual ~NewTabPageAdServingDelegate() = default;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_NEW_TAB_PAGE_AD_SERVING_DELEGATE_H_
