/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ml/data/text_data.h"

#include <utility>

namespace catsxp_ads::ml {

TextData::TextData() : Data(DataType::kText) {}

TextData::TextData(std::string text)
    : Data(DataType::kText), text_(std::move(text)) {}

const std::string& TextData::GetText() const {
  return text_;
}

}  // namespace catsxp_ads::ml
