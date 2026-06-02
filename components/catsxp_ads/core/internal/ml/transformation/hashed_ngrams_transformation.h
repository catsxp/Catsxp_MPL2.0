/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/transformation.h"

namespace catsxp_ads::ml {

class HashVectorizer;

class HashedNGramsTransformation final : public Transformation {
 public:
  HashedNGramsTransformation();
  HashedNGramsTransformation(int bucket_count, std::vector<uint32_t> subgrams);

  HashedNGramsTransformation(const HashedNGramsTransformation&) = delete;
  HashedNGramsTransformation& operator=(const HashedNGramsTransformation&) =
      delete;

  ~HashedNGramsTransformation() override;

  // Transformation:
  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;

 private:
  std::unique_ptr<HashVectorizer> hash_vectorizer_;
};

}  // namespace catsxp_ads::ml

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_HASHED_NGRAMS_TRANSFORMATION_H_
