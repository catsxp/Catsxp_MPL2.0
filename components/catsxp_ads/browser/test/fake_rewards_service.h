/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_REWARDS_SERVICE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_REWARDS_SERVICE_H_

#include "catsxp/components/catsxp_rewards/content/rewards_notification_service.h"
#include "catsxp/components/catsxp_rewards/core/buildflags/buildflags.h"
#include "catsxp/components/catsxp_rewards/core/mojom/rewards.mojom-forward.h"

#if BUILDFLAG(ENABLE_CATSXP_REWARDS)
#include <cstdint>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "catsxp/components/catsxp_rewards/content/rewards_service.h"

namespace catsxp_ads::test {

// Minimal stub implementation of `catsxp_rewards::RewardsService` for unit
// tests. All methods are no-ops or immediately run their callbacks with safe
// default values. Only `GetRewardsWallet` matters for `AdsServiceImpl`
// initialization; it returns `nullptr` (no wallet) by default.
class FakeRewardsService : public catsxp_rewards::RewardsService {
 public:
  FakeRewardsService();

  FakeRewardsService(const FakeRewardsService&) = delete;
  FakeRewardsService& operator=(const FakeRewardsService&) = delete;

  ~FakeRewardsService() override;

  // catsxp_rewards::RewardsService:
  bool IsInitialized() override;
  void CreateRewardsWallet(const std::string& country,
                           CreateRewardsWalletCallback callback) override;
  std::string GetCountryCode() const override;
  void GetUserType(base::OnceCallback<void(catsxp_rewards::mojom::UserType)>
                       callback) override;
  bool IsTermsOfServiceUpdateRequired() override;
  void AcceptTermsOfServiceUpdate() override;
  void GetAvailableCountries(
      GetAvailableCountriesCallback callback) const override;
  void GetRewardsParameters(
      catsxp_rewards::GetRewardsParametersCallback callback) override;
  void FetchUICards(FetchUICardsCallback callback) override;
  void GetActivityInfoList(
      uint32_t start,
      uint32_t limit,
      catsxp_rewards::mojom::ActivityInfoFilterPtr filter,
      catsxp_rewards::GetPublisherInfoListCallback callback) override;
  void GetPublishersVisitedCount(
      base::OnceCallback<void(int)> callback) override;
  void GetExcludedList(
      catsxp_rewards::GetPublisherInfoListCallback callback) override;
  void RestorePublishers() override;
  void GetReconcileStamp(
      catsxp_rewards::GetReconcileStampCallback callback) override;
  void GetPublisherMinVisitTime(
      catsxp_rewards::GetPublisherMinVisitTimeCallback callback) override;
  void SetPublisherMinVisitTime(int duration_in_seconds) const override;
  void GetPublisherMinVisits(
      catsxp_rewards::GetPublisherMinVisitsCallback callback) override;
  void SetPublisherMinVisits(int visits) const override;
  void GetBalanceReport(
      uint32_t month,
      uint32_t year,
      catsxp_rewards::GetBalanceReportCallback callback) override;
  void NotifyPublisherPageVisit(
      catsxp_rewards::mojom::VisitDataPtr visit_data) override;
  void NotifyPublisherPageVisit(uint64_t tab_id,
                                const std::string& url) override;
  void GetPublisherBanner(
      const std::string& publisher_id,
      catsxp_rewards::GetPublisherBannerCallback callback) override;
  void OnTip(const std::string& publisher_key,
             double amount,
             bool recurring,
             catsxp_rewards::OnTipCallback callback) override;
  void RemoveRecurringTip(const std::string& publisher_key) override;
  void SendContribution(const std::string& publisher_id,
                        double amount,
                        bool set_monthly,
                        base::OnceCallback<void(bool)> callback) override;
  void GetRecurringTips(
      catsxp_rewards::GetRecurringTipsCallback callback) override;
  void GetOneTimeTips(catsxp_rewards::GetOneTimeTipsCallback callback) override;
  void SetPublisherExclude(const std::string& publisher_key,
                           bool exclude) override;
  catsxp_rewards::RewardsNotificationService* GetNotificationService()
      const override;
  void GetRewardsInternalsInfo(
      catsxp_rewards::GetRewardsInternalsInfoCallback callback) override;
  void RefreshPublisher(
      const std::string& publisher_key,
      catsxp_rewards::RefreshPublisherCallback callback) override;
  void SaveRecurringTip(const std::string& publisher_key,
                        double amount,
                        catsxp_rewards::OnTipCallback callback) override;
  const catsxp_rewards::RewardsNotificationService::RewardsNotificationsMap&
  GetAllNotifications() override;
  void IsPublisherRegistered(const std::string& publisher_id,
                             base::OnceCallback<void(bool)> callback) override;
  void GetPublisherInfo(
      const std::string& publisher_key,
      catsxp_rewards::GetPublisherInfoCallback callback) override;
  void GetPublisherPanelInfo(
      const std::string& publisher_key,
      catsxp_rewards::GetPublisherInfoCallback callback) override;
  void SavePublisherInfo(
      uint64_t window_id,
      catsxp_rewards::mojom::PublisherInfoPtr publisher_info,
      catsxp_rewards::SavePublisherInfoCallback callback) override;
  void GetShareURL(const base::flat_map<std::string, std::string>& args,
                   catsxp_rewards::GetShareURLCallback callback) override;
  void FetchBalance(catsxp_rewards::FetchBalanceCallback callback) override;
  void GetExternalWallet(
      catsxp_rewards::GetExternalWalletCallback callback) override;
  std::string GetExternalWalletType() const override;
  std::vector<std::string> GetExternalWalletProviders() const override;
  void BeginExternalWalletLogin(
      const std::string& wallet_type,
      BeginExternalWalletLoginCallback callback) override;
  void ConnectExternalWallet(
      const std::string& path,
      const std::string& query,
      catsxp_rewards::ConnectExternalWalletCallback callback) override;
  void ConnectExternalWallet(
      const std::string& provider,
      const base::flat_map<std::string, std::string>& args,
      catsxp_rewards::ConnectExternalWalletCallback callback) override;
  void GetAllContributions(
      catsxp_rewards::GetAllContributionsCallback callback) override;
  void WriteDiagnosticLog(const std::string& file,
                          int line,
                          int verbose_level,
                          const std::string& message) override;
  void LoadDiagnosticLog(
      int num_lines,
      catsxp_rewards::LoadDiagnosticLogCallback callback) override;
  void ClearDiagnosticLog(
      catsxp_rewards::ClearDiagnosticLogCallback callback) override;
  void CompleteReset(catsxp_rewards::SuccessCallback callback) override;
  void GetEventLogs(catsxp_rewards::GetEventLogsCallback callback) override;
  void GetRewardsWallet(
      catsxp_rewards::GetRewardsWalletCallback callback) override;
  void GetEnvironment(catsxp_rewards::GetEnvironmentCallback callback) override;
  catsxp_rewards::p3a::ConversionMonitor* GetP3AConversionMonitor() override;
  void OnRewardsPageShown() override;
};

}  // namespace catsxp_ads::test

#endif  // BUILDFLAG(ENABLE_CATSXP_REWARDS)

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_BROWSER_TEST_FAKE_REWARDS_SERVICE_H_
