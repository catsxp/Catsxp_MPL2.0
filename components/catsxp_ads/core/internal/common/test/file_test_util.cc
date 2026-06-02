/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/file_test_util.h"

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/file_path_test_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/internal/tag_parser_test_util_internal.h"

namespace catsxp_ads::test {

std::optional<std::string> MaybeReadFileToString(const std::string& name) {
  const base::FilePath path = DataPath().AppendASCII(name);

  std::string contents;
  if (!base::ReadFileToString(path, &contents)) {
    return std::nullopt;
  }

  return contents;
}

std::optional<std::string> MaybeReadFileToStringAndReplaceTags(
    const std::string& name) {
  std::optional<std::string> contents = MaybeReadFileToString(name);
  if (!contents) {
    return std::nullopt;
  }

  ParseAndReplaceTags(*contents);

  return contents;
}

}  // namespace catsxp_ads::test
