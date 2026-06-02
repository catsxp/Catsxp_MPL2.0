/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_ALGORITHM_SPLIT_VECTOR_UTIL_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_ALGORITHM_SPLIT_VECTOR_UTIL_H_

#include <iterator>
#include <vector>

#include "base/check_op.h"

namespace catsxp_ads {

template <typename T>
std::vector<std::vector<T>> SplitVector(const std::vector<T>& elements,
                                        int chunk_size) {
  CHECK_NE(0, chunk_size);

  std::vector<std::vector<T>> result;
  result.reserve((elements.size() + chunk_size - 1) / chunk_size);

  auto begin = elements.cbegin();
  const auto end = elements.cend();
  while (begin != end) {
    const auto next = std::distance(begin, end) >= chunk_size
                          ? std::next(begin, chunk_size)
                          : end;

    result.emplace_back(begin, next);

    begin = next;
  }

  return result;
}

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_COMMON_ALGORITHM_SPLIT_VECTOR_UTIL_H_
