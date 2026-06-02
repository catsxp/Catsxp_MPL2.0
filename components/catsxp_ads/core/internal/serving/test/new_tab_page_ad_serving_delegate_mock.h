/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_

#include "catsxp/components/catsxp_ads/core/internal/serving/new_tab_page_ad_serving_delegate.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class NewTabPageAdServingDelegateMock : public NewTabPageAdServingDelegate {
 public:
  NewTabPageAdServingDelegateMock();

  NewTabPageAdServingDelegateMock(const NewTabPageAdServingDelegateMock&) =
      delete;
  NewTabPageAdServingDelegateMock& operator=(
      const NewTabPageAdServingDelegateMock&) = delete;

  ~NewTabPageAdServingDelegateMock() override;

  MOCK_METHOD(void, OnOpportunityAroseToServeNewTabPageAd, ());

  MOCK_METHOD(void, OnDidServeNewTabPageAd, (const NewTabPageAdInfo&));
  MOCK_METHOD(void, OnFailedToServeNewTabPageAd, ());
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_TEST_NEW_TAB_PAGE_AD_SERVING_DELEGATE_MOCK_H_
