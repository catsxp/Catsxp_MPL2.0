/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"

#include <memory>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_factory.h"

namespace catsxp_ads {

std::string GetUrlHost(UrlHostType type) {
  std::unique_ptr<UrlHostInterface> url_host = UrlHostFactory::Build(type);
  CHECK(url_host);

  return url_host->Get();
}

}  // namespace catsxp_ads
