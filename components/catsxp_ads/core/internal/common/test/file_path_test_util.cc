/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/test/file_path_test_util.h"

#include "base/files/file_path.h"
#include "base/path_service.h"

namespace catsxp_ads::test {

namespace {

base::FilePath RootPath() {
  return base::PathService::CheckedGet(base::DIR_SRC_TEST_DATA_ROOT)
      .AppendASCII("catsxp")
      .AppendASCII("components")
      .AppendASCII("catsxp_ads");
}

}  // namespace

base::FilePath DataPath() {
  return RootPath().AppendASCII("core").AppendASCII("test").AppendASCII("data");
}

base::FilePath ResourceComponentsDataPath() {
  return DataPath().AppendASCII("resources").AppendASCII("components");
}

base::FilePath UrlResponsesDataPath() {
  return DataPath().AppendASCII("url_responses");
}

}  // namespace catsxp_ads::test
