/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEST_TEXT_CLASSIFICATION_TEST_HELPER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEST_TEXT_CLASSIFICATION_TEST_HELPER_H_

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/resource/text_classification_resource.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_processor.h"

namespace catsxp_ads::test {

class TextClassificationHelper final {
 public:
  TextClassificationHelper();

  TextClassificationHelper(const TextClassificationHelper&) = delete;
  TextClassificationHelper& operator=(const TextClassificationHelper&) = delete;

  ~TextClassificationHelper();

  void Simulate();

  static SegmentList Expectation();

 private:
  TextClassificationResource resource_;
  TextClassificationProcessor processor_;
};

}  // namespace catsxp_ads::test

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEST_TEXT_CLASSIFICATION_TEST_HELPER_H_
