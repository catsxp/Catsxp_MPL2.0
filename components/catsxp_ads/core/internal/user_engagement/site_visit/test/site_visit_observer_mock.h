/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_TEST_SITE_VISIT_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_TEST_SITE_VISIT_OBSERVER_MOCK_H_

#include <cstdint>

#include "catsxp/components/catsxp_ads/core/internal/user_engagement/site_visit/site_visit_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class SiteVisitObserverMock : public SiteVisitObserver {
 public:
  SiteVisitObserverMock();

  SiteVisitObserverMock(const SiteVisitObserverMock&) = delete;
  SiteVisitObserverMock& operator=(const SiteVisitObserverMock&) = delete;

  ~SiteVisitObserverMock() override;

  MOCK_METHOD(void, OnMaybeLandOnPage, (const AdInfo&, base::TimeDelta));
  MOCK_METHOD(void, OnDidSuspendPageLand, (int32_t, base::TimeDelta));
  MOCK_METHOD(void, OnDidResumePageLand, (int32_t, base::TimeDelta));
  MOCK_METHOD(void, OnDidLandOnPage, (int32_t, int, const AdInfo&));
  MOCK_METHOD(void, OnDidNotLandOnPage, (int32_t, const AdInfo&));
  MOCK_METHOD(void, OnCanceledPageLand, (int32_t, const AdInfo&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_TEST_SITE_VISIT_OBSERVER_MOCK_H_
