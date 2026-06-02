/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/test/fake_rewards_service.h"

#include <optional>
#include <utility>
#include <vector>

#include "base/functional/callback.h"
#include "base/no_destructor.h"
#include "catsxp/components/catsxp_rewards/content/rewards_notification_service.h"
#include "catsxp/components/catsxp_rewards/core/mojom/rewards.mojom.h"

namespace catsxp_ads::test {

FakeRewardsService::FakeRewardsService() = default;

FakeRewardsService::~FakeRewardsService() = default;

bool FakeRewardsService::IsInitialized() {
  return false;
}

void FakeRewardsService::CreateRewardsWallet(
    const std::string& /*country*/,
    CreateRewardsWalletCallback callback) {
  std::move(callback).Run(
      catsxp_rewards::mojom::CreateRewardsWalletResult::kSuccess);
}

std::string FakeRewardsService::GetCountryCode() const {
  return "";
}

void FakeRewardsService::GetUserType(
    base::OnceCallback<void(catsxp_rewards::mojom::UserType)> callback) {
  std::move(callback).Run(catsxp_rewards::mojom::UserType::kUnconnected);
}

bool FakeRewardsService::IsTermsOfServiceUpdateRequired() {
  return false;
}

void FakeRewardsService::AcceptTermsOfServiceUpdate() {}

void FakeRewardsService::GetAvailableCountries(
    GetAvailableCountriesCallback callback) const {
  std::move(callback).Run({});
}

void FakeRewardsService::GetRewardsParameters(
    catsxp_rewards::GetRewardsParametersCallback callback) {
  std::move(callback).Run(nullptr);
}

void FakeRewardsService::FetchUICards(FetchUICardsCallback callback) {
  std::move(callback).Run(std::nullopt);
}

void FakeRewardsService::GetActivityInfoList(
    uint32_t /*start*/,
    uint32_t /*limit*/,
    catsxp_rewards::mojom::ActivityInfoFilterPtr /*filter*/,
    catsxp_rewards::GetPublisherInfoListCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::GetPublishersVisitedCount(
    base::OnceCallback<void(int)> callback) {
  std::move(callback).Run(0);
}

void FakeRewardsService::GetExcludedList(
    catsxp_rewards::GetPublisherInfoListCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::RestorePublishers() {}

void FakeRewardsService::GetReconcileStamp(
    catsxp_rewards::GetReconcileStampCallback callback) {
  std::move(callback).Run(0);
}

void FakeRewardsService::GetPublisherMinVisitTime(
    catsxp_rewards::GetPublisherMinVisitTimeCallback callback) {
  std::move(callback).Run(0);
}

void FakeRewardsService::SetPublisherMinVisitTime(
    int /*duration_in_seconds*/) const {}

void FakeRewardsService::GetPublisherMinVisits(
    catsxp_rewards::GetPublisherMinVisitsCallback callback) {
  std::move(callback).Run(0);
}

void FakeRewardsService::SetPublisherMinVisits(int /*visits*/) const {}

void FakeRewardsService::GetBalanceReport(
    uint32_t /*month*/,
    uint32_t /*year*/,
    catsxp_rewards::GetBalanceReportCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED, nullptr);
}

void FakeRewardsService::NotifyPublisherPageVisit(
    catsxp_rewards::mojom::VisitDataPtr /*visit_data*/) {}

void FakeRewardsService::NotifyPublisherPageVisit(uint64_t /*tab_id*/,
                                                  const std::string& /*url*/) {}

void FakeRewardsService::GetPublisherBanner(
    const std::string& /*publisher_id*/,
    catsxp_rewards::GetPublisherBannerCallback callback) {
  std::move(callback).Run(nullptr);
}

void FakeRewardsService::OnTip(const std::string& /*publisher_key*/,
                               double /*amount*/,
                               bool /*recurring*/,
                               catsxp_rewards::OnTipCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED);
}

void FakeRewardsService::RemoveRecurringTip(
    const std::string& /*publisher_key*/) {}

void FakeRewardsService::SendContribution(
    const std::string& /*publisher_id*/,
    double /*amount*/,
    bool /*set_monthly*/,
    base::OnceCallback<void(bool)> callback) {
  std::move(callback).Run(false);
}

void FakeRewardsService::GetRecurringTips(
    catsxp_rewards::GetRecurringTipsCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::GetOneTimeTips(
    catsxp_rewards::GetOneTimeTipsCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::SetPublisherExclude(
    const std::string& /*publisher_key*/,
    bool /*exclude*/) {}

catsxp_rewards::RewardsNotificationService*
FakeRewardsService::GetNotificationService() const {
  return nullptr;
}

void FakeRewardsService::GetRewardsInternalsInfo(
    catsxp_rewards::GetRewardsInternalsInfoCallback callback) {
  std::move(callback).Run(nullptr);
}

void FakeRewardsService::RefreshPublisher(
    const std::string& /*publisher_key*/,
    catsxp_rewards::RefreshPublisherCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::PublisherStatus::NOT_VERIFIED,
                          "");
}

void FakeRewardsService::SaveRecurringTip(
    const std::string& /*publisher_key*/,
    double /*amount*/,
    catsxp_rewards::OnTipCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED);
}

const catsxp_rewards::RewardsNotificationService::RewardsNotificationsMap&
FakeRewardsService::GetAllNotifications() {
  static const base::NoDestructor<
      catsxp_rewards::RewardsNotificationService::RewardsNotificationsMap>
      kEmpty;
  return *kEmpty;
}

void FakeRewardsService::IsPublisherRegistered(
    const std::string& /*publisher_id*/,
    base::OnceCallback<void(bool)> callback) {
  std::move(callback).Run(false);
}

void FakeRewardsService::GetPublisherInfo(
    const std::string& /*publisher_key*/,
    catsxp_rewards::GetPublisherInfoCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED, nullptr);
}

void FakeRewardsService::GetPublisherPanelInfo(
    const std::string& /*publisher_key*/,
    catsxp_rewards::GetPublisherInfoCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED, nullptr);
}

void FakeRewardsService::SavePublisherInfo(
    uint64_t /*window_id*/,
    catsxp_rewards::mojom::PublisherInfoPtr /*publisher_info*/,
    catsxp_rewards::SavePublisherInfoCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Result::FAILED);
}

void FakeRewardsService::GetShareURL(
    const base::flat_map<std::string, std::string>& /*args*/,
    catsxp_rewards::GetShareURLCallback callback) {
  std::move(callback).Run("");
}

void FakeRewardsService::FetchBalance(
    catsxp_rewards::FetchBalanceCallback callback) {
  std::move(callback).Run(nullptr);
}

void FakeRewardsService::GetExternalWallet(
    catsxp_rewards::GetExternalWalletCallback callback) {
  std::move(callback).Run(nullptr);
}

std::string FakeRewardsService::GetExternalWalletType() const {
  return "";
}

std::vector<std::string> FakeRewardsService::GetExternalWalletProviders()
    const {
  return {};
}

void FakeRewardsService::BeginExternalWalletLogin(
    const std::string& /*wallet_type*/,
    BeginExternalWalletLoginCallback callback) {
  std::move(callback).Run(nullptr);
}

void FakeRewardsService::ConnectExternalWallet(
    const std::string& /*path*/,
    const std::string& /*query*/,
    catsxp_rewards::ConnectExternalWalletCallback callback) {
  std::move(callback).Run(
      catsxp_rewards::mojom::ConnectExternalWalletResult::kUnexpected);
}

void FakeRewardsService::ConnectExternalWallet(
    const std::string& /*provider*/,
    const base::flat_map<std::string, std::string>& /*args*/,
    catsxp_rewards::ConnectExternalWalletCallback callback) {
  std::move(callback).Run(
      catsxp_rewards::mojom::ConnectExternalWalletResult::kUnexpected);
}

void FakeRewardsService::GetAllContributions(
    catsxp_rewards::GetAllContributionsCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::WriteDiagnosticLog(const std::string& /*file*/,
                                            int /*line*/,
                                            int /*verbose_level*/,
                                            const std::string& /*message*/) {}

void FakeRewardsService::LoadDiagnosticLog(
    int /*num_lines*/,
    catsxp_rewards::LoadDiagnosticLogCallback callback) {
  std::move(callback).Run("");
}

void FakeRewardsService::ClearDiagnosticLog(
    catsxp_rewards::ClearDiagnosticLogCallback callback) {
  std::move(callback).Run(true);
}

void FakeRewardsService::CompleteReset(
    catsxp_rewards::SuccessCallback callback) {
  std::move(callback).Run(false);
}

void FakeRewardsService::GetEventLogs(
    catsxp_rewards::GetEventLogsCallback callback) {
  std::move(callback).Run({});
}

void FakeRewardsService::GetRewardsWallet(
    catsxp_rewards::GetRewardsWalletCallback callback) {
  auto wallet = catsxp_rewards::mojom::RewardsWallet::New();
  wallet->payment_id = "foo";
  wallet->recovery_seed = std::vector<uint8_t>(32, 0);
  std::move(callback).Run(std::move(wallet));
}

void FakeRewardsService::GetEnvironment(
    catsxp_rewards::GetEnvironmentCallback callback) {
  std::move(callback).Run(catsxp_rewards::mojom::Environment::kProduction);
}

catsxp_rewards::p3a::ConversionMonitor*
FakeRewardsService::GetP3AConversionMonitor() {
  return nullptr;
}

void FakeRewardsService::OnRewardsPageShown() {}

}  // namespace catsxp_ads::test
