/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_RANDOM_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_RANDOM_UTIL_H_

namespace catsxp_ads {

double GeneratePacingRandomNumber();

class ScopedPacingRandomNumberSetterForTesting final {
 public:
  explicit ScopedPacingRandomNumberSetterForTesting(double number);

  ScopedPacingRandomNumberSetterForTesting(
      const ScopedPacingRandomNumberSetterForTesting&) = delete;
  ScopedPacingRandomNumberSetterForTesting& operator=(
      const ScopedPacingRandomNumberSetterForTesting&) = delete;

  ~ScopedPacingRandomNumberSetterForTesting();
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_RANDOM_UTIL_H_
