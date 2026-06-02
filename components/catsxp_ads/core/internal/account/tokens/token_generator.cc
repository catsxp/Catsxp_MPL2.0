/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/tokens/token_generator.h"

namespace catsxp_ads {

cbr::TokenList TokenGenerator::Generate(size_t count) const {
  return cbr::TokenList(count);
}

}  // namespace catsxp_ads
