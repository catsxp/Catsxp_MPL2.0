/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_DATA_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_DATA_H_

#include "catsxp/components/catsxp_ads/core/internal/ml/data/data_types.h"

namespace catsxp_ads::ml {

class Data {
 public:
  explicit Data(DataType type);

  Data(const Data&) = delete;
  Data& operator=(const Data&) = delete;

  virtual ~Data();

  DataType GetType() const;

 protected:
  const DataType type_;
};

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_DATA_DATA_H_
