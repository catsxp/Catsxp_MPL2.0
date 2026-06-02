/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision.h"

#include <optional>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/ads_client/ads_client_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/logging_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/url_request/subdivision_url_request.h"
#include "catsxp/components/catsxp_ads/core/internal/prefs/pref_path_util.h"
#include "catsxp/components/catsxp_ads/core/internal/settings/settings.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client.h"

namespace catsxp_ads {

namespace {

bool DoesRequireResource() {
  // Require resource only if:
  // - The user has joined Catsxp Rewards and opted into notification ads.
  return UserHasOptedInToNotificationAds();
}

}  // namespace

Subdivision::Subdivision() {
  ads_client_observation_.Observe(&GetAdsClient());
}

Subdivision::~Subdivision() = default;

void Subdivision::AddObserver(SubdivisionObserver* const observer) {
  observers_.AddObserver(observer);
}

void Subdivision::RemoveObserver(SubdivisionObserver* const observer) {
  observers_.RemoveObserver(observer);
}

///////////////////////////////////////////////////////////////////////////////

void Subdivision::Initialize() {
  MaybeRequireSubdivision();

  MaybePeriodicallyFetchSubdivision();
}

void Subdivision::MaybeRequireSubdivision() {
  DoesRequireResource() ? InitializeSubdivisionUrlRequest()
                        : ShutdownSubdivisionUrlRequest();
}

void Subdivision::InitializeSubdivisionUrlRequest() {
  if (!subdivision_url_request_) {
    BLOG(1, "Initialize subdivision URL request");
    subdivision_url_request_ = std::make_unique<SubdivisionUrlRequest>();
    subdivision_url_request_->SetDelegate(this);
  }
}

void Subdivision::ShutdownSubdivisionUrlRequest() {
  if (subdivision_url_request_) {
    subdivision_url_request_.reset();
    BLOG(1, "Shutdown subdivision URL request");
  }
}

void Subdivision::MaybePeriodicallyFetchSubdivision() {
  if (subdivision_url_request_) {
    subdivision_url_request_->PeriodicallyFetch();
  }
}

void Subdivision::NotifyDidUpdateSubdivision(const std::string& subdivision) {
  observers_.Notify(&SubdivisionObserver::OnDidUpdateSubdivision, subdivision);
}

void Subdivision::OnNotifyDidInitializeAds() {
  Initialize();
}

void Subdivision::OnNotifyPrefDidChange(const std::string& path) {
  if (DoesMatchUserHasJoinedCatsxpRewardsPrefPath(path) ||
      DoesMatchUserHasOptedInToNotificationAdsPrefPath(path)) {
    // This condition should include all the preferences that are present in the
    // `DoesRequireResource` function.
    Initialize();
  }
}

void Subdivision::OnDidFetchSubdivision(const std::string& subdivision) {
  CHECK(!subdivision.empty());

  std::optional<std::string> country_code =
      GetSubdivisionCountryCode(subdivision);
  std::optional<std::string> subdivision_code = GetSubdivisionCode(subdivision);

  if (!country_code || !subdivision_code) {
    return;
  }

  NotifyDidUpdateSubdivision(subdivision);
}

}  // namespace catsxp_ads
