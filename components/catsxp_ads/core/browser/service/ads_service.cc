/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/browser/service/ads_service.h"

#include <utility>

#include "base/check.h"

namespace catsxp_ads {

AdsService::AdsService(std::unique_ptr<Delegate> delegate)
    : delegate_(std::move(delegate)) {}

AdsService::~AdsService() = default;

void AdsService::AddObserver(AdsServiceObserver* const observer) {
  CHECK(observer);

  observers_.AddObserver(observer);
}

void AdsService::RemoveObserver(AdsServiceObserver* const observer) {
  CHECK(observer);

  observers_.RemoveObserver(observer);
}

}  // namespace catsxp_ads
