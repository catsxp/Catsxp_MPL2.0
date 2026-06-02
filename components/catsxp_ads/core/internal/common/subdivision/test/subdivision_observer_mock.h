/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_TEST_SUBDIVISION_OBSERVER_MOCK_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_TEST_SUBDIVISION_OBSERVER_MOCK_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_observer.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace catsxp_ads {

class SubdivisionObserverMock : public SubdivisionObserver {
 public:
  SubdivisionObserverMock();

  SubdivisionObserverMock(const SubdivisionObserverMock&) = delete;
  SubdivisionObserverMock& operator=(const SubdivisionObserverMock&) = delete;

  ~SubdivisionObserverMock() override;

  MOCK_METHOD(void, OnDidUpdateSubdivision, (const std::string&));
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_TEST_SUBDIVISION_OBSERVER_MOCK_H_
