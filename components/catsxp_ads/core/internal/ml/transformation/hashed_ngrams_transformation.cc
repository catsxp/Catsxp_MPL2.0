/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/hashed_ngrams_transformation.h"

#include <map>
#include <utility>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/vector_data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/hash_vectorizer.h"

namespace catsxp_ads::ml {

HashedNGramsTransformation::HashedNGramsTransformation() {
  hash_vectorizer_ = std::make_unique<HashVectorizer>();
}

HashedNGramsTransformation::HashedNGramsTransformation(
    int bucket_count,
    std::vector<uint32_t> subgrams) {
  hash_vectorizer_ =
      std::make_unique<HashVectorizer>(bucket_count, std::move(subgrams));
}

HashedNGramsTransformation::~HashedNGramsTransformation() = default;

std::unique_ptr<Data> HashedNGramsTransformation::Apply(
    const std::unique_ptr<Data>& input_data) const {
  CHECK(input_data);

  // TODO(https://github.com/catsxp/catsxp-browser/issues/31180): Refactor
  // TextProcessing to make it more reliable.
  if (input_data->GetType() != DataType::kText) {
    return {};
  }

  const auto* const text_data = static_cast<TextData*>(input_data.get());

  const std::map<unsigned, double> frequences =
      hash_vectorizer_->GetFrequencies(text_data->GetText());
  const int dimension_count = hash_vectorizer_->GetBucketCount();

  return std::make_unique<VectorData>(dimension_count, frequences);
}

}  // namespace catsxp_ads::ml
