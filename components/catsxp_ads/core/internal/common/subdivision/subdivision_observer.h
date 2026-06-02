/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"

namespace catsxp_ads {

class SubdivisionObserver : public base::CheckedObserver {
 public:
  // Invoked when the subdivision has updated.
  virtual void OnDidUpdateSubdivision(const std::string& subdivision) {}
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_SUBDIVISION_SUBDIVISION_OBSERVER_H_
