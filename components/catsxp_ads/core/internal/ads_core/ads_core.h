/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_H_

#include <memory>
#include <string>

#include "base/containers/flat_set.h"
#include "catsxp/components/catsxp_ads/core/internal/account/account.h"
#include "catsxp/components/catsxp_ads/core/internal/ad_units/ad_handler.h"
#include "catsxp/components/catsxp_ads/core/internal/reminders/reminders.h"
#include "catsxp/components/catsxp_ads/core/internal/studies/studies.h"
#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_idle_detection/user_idle_detection.h"
#include "catsxp/components/catsxp_ads/core/internal/user_engagement/reactions/reactions.h"

namespace catsxp_ads {

class TokenGeneratorInterface;

class AdsCore final {
 public:
  explicit AdsCore(std::unique_ptr<TokenGeneratorInterface> token_generator);

  AdsCore(const AdsCore& other) = delete;
  AdsCore& operator=(const AdsCore& other) = delete;

  AdsCore(AdsCore&& other) noexcept = delete;
  AdsCore& operator=(AdsCore&& other) noexcept = delete;

  ~AdsCore();

  // Provides methods for generating tokens for refilling and redeeming
  // confirmation tokens.
  TokenGeneratorInterface* GetTokenGenerator();

  // Provides methods for managing user rewards, wallets, account statements,
  // and deposits.
  Account& GetAccount();

  // Provides methods for serving and triggering events for various types of
  // ads, including new tab page ads, notification ads, and search result ads.
  AdHandler& GetAdHandler();

  // Provides methods for engaging with ads, such as liking, disliking, marking
  // as inappropriate, and saving ads.
  Reactions& GetReactions();

  // Updates the reporting state for a creative instance ID, enabling or
  // disabling metrics reporting.
  void UpdateReportMetricState(
      const std::string& creative_instance_id,
      mojom::NewTabPageAdMetricType mojom_ad_metric_type);

  // Returns true if metrics should be reported for the given creative instance
  // ID, otherwise false.
  bool ShouldReportMetric(const std::string& creative_instance_id) const;

 private:
  const std::unique_ptr<TokenGeneratorInterface> token_generator_;

  Account account_;

  AdHandler ad_handler_;

  Reactions reactions_;

  // Handles the delivery of helpful reminders to users on how to interact with
  // Catsxp Ads.
  Reminders reminders_;

  // Handles notifying observers when the user becomes active or idle, and
  // whether the screen is locked.
  UserIdleDetection user_idle_detection_;

  // Handles user studies, a set of experiments conducted on the client.
  Studies studies_;

  // Metrics for the given creative instance ID should not be sent
  // if the ID exists in this set.
  base::flat_set</*creative_instance_id*/ std::string> disable_metrics_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_ADS_CORE_ADS_CORE_H_
