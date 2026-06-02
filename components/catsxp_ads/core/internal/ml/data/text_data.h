/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_

#include <string>

#include "catsxp/components/catsxp_ads/core/internal/ml/data/data.h"

namespace catsxp_ads::ml {

class TextData final : public Data {
 public:
  TextData();
  explicit TextData(std::string text);

  const std::string& GetText() const;

 private:
  const std::string text_;
};

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_TEXT_DATA_H_
