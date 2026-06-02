/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/data/data.h"

namespace catsxp_ads::ml {

Data::Data(DataType type) : type_(type) {}

Data::~Data() = default;

DataType Data::GetType() const {
  return type_;
}

}  // namespace catsxp_ads::ml
