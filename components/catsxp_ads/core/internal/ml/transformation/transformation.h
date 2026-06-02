/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_

#include <memory>
#include <vector>

namespace catsxp_ads::ml {

class Data;

class Transformation {
 public:
  virtual ~Transformation();

  virtual std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const = 0;
};

using TransformationPtr = std::unique_ptr<Transformation>;
using TransformationVector = std::vector<TransformationPtr>;

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_TRANSFORMATION_H_
