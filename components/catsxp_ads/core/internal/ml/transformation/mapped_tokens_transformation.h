/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/transformation.h"

namespace catsxp_ads {

namespace neural_text_classification::flat {
struct MappedTokenTransformation;
}  // namespace neural_text_classification::flat

namespace ml {

class MappedTokensTransformation final : public Transformation {
 public:
  explicit MappedTokensTransformation(
      const neural_text_classification::flat::MappedTokenTransformation&
          mapped_token_transformation);

  ~MappedTokensTransformation() override;

  std::optional<std::map<uint32_t, double>> GetCategoryFrequencies(
      const std::vector<std::string>& words) const;

  // Transformation:
  std::unique_ptr<Data> Apply(
      const std::unique_ptr<Data>& input_data) const override;

 private:
  const raw_ref<
      const neural_text_classification::flat::MappedTokenTransformation>
      mapped_token_transformation_;
};

}  // namespace ml

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ML_TRANSFORMATION_MAPPED_TOKENS_TRANSFORMATION_H_
