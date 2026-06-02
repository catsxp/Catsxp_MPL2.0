/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/lowercase_transformation.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/data.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"

namespace catsxp_ads::ml {

LowercaseTransformation::LowercaseTransformation() = default;

std::unique_ptr<Data> LowercaseTransformation::Apply(
    const std::unique_ptr<Data>& input_data) const {
  CHECK(input_data);

  if (input_data->GetType() != DataType::kText) {
    return {};
  }

  const auto* const text_data = static_cast<TextData*>(input_data.get());

  std::string lowercase_text = base::ToLowerASCII(text_data->GetText());

  return std::make_unique<TextData>(std::move(lowercase_text));
}

}  // namespace catsxp_ads::ml
