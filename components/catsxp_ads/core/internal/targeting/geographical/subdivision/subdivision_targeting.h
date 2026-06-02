/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_

#include <optional>
#include <string>

#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/common/subdivision/subdivision_observer.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

class SubdivisionTargeting final : public AdsClientNotifierObserver,
                                   public SubdivisionObserver {
 public:
  SubdivisionTargeting();

  SubdivisionTargeting(const SubdivisionTargeting&) = delete;
  SubdivisionTargeting& operator=(const SubdivisionTargeting&) = delete;

  ~SubdivisionTargeting() override;

  bool IsDisabled() const;

  bool ShouldAutoDetect() const;

  static bool ShouldAllow();

  const std::string& GetSubdivision() const;

 private:
  void MaybeInitialize();

  void MaybeRequireSubdivision();

  void DisableSubdivision();

  void AutoDetectSubdivision();

  void MaybeAllowForCountry(const std::string& country_code);

  bool ShouldFetchSubdivision();
  void MaybeFetchSubdivision();

  void MaybeAllowAndFetchSubdivisionForLocale(const std::string& locale);

  void SetAutoDetectedSubdivision(const std::string& subdivision);
  void UpdateAutoDetectedSubdivision();
  const std::string& GetLazyAutoDetectedSubdivision() const;

  void SetUserSelectedSubdivision(const std::string& subdivision);
  void UpdateUserSelectedSubdivision();
  const std::string& GetLazyUserSelectedSubdivision() const;

  // AdsClientNotifierObserver:
  void OnNotifyDidInitializeAds() override;
  void OnNotifyPrefDidChange(const std::string& path) override;

  // SubdivisionObserver:
  void OnDidUpdateSubdivision(const std::string& subdivision) override;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  mutable std::optional<std::string> auto_detected_subdivision_;
  mutable std::optional<std::string> user_selected_subdivision_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_GEOGRAPHICAL_SUBDIVISION_SUBDIVISION_TARGETING_H_
