/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_factory.h"

#include <ostream>  // IWYU pragma: keep
#include <utility>

#include "base/notreached.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/anonymous_search_url_host.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/anonymous_url_host.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/geo_url_host.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/non_anonymous_url_host.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/hosts/static_url_host.h"

namespace catsxp_ads {

std::unique_ptr<UrlHostInterface> UrlHostFactory::Build(UrlHostType type) {
  switch (type) {
    case UrlHostType::kStatic: {
      return std::make_unique<StaticUrlHost>();
    }

    case UrlHostType::kGeo: {
      return std::make_unique<GeoUrlHost>();
    }

    case UrlHostType::kNonAnonymous: {
      return std::make_unique<NonAnonymousUrlHost>();
    }

    case UrlHostType::kAnonymous: {
      return std::make_unique<AnonymousUrlHost>();
    }

    case UrlHostType::kAnonymousSearch: {
      return std::make_unique<AnonymousSearchUrlHost>();
    }
  }

  NOTREACHED() << "Unexpected value for UrlHostType: "
               << std::to_underlying(type);
}

}  // namespace catsxp_ads
