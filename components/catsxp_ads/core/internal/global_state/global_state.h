/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_H_

#include <memory>

#include "base/files/file_path.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

// TODO(https://github.com/catsxp/catsxp-browser/issues/37622): Deprecate
// `GlobalState`.

class AdHistoryManager;
class AdsClient;
class AdsCore;
class AdsNotifierManager;
class BrowserManager;
class ClientStateManager;
class DatabaseManager;
class DiagnosticManager;
class GlobalStateHolder;
class NotificationAdManager;
class TabManager;
class TokenGeneratorInterface;
class TokenStateManager;
class UserActivityManager;

class GlobalState final {
 public:
  GlobalState(AdsClient& ads_client,
              const base::FilePath& database_path,
              std::unique_ptr<TokenGeneratorInterface> token_generator);

  GlobalState(const GlobalState& other) = delete;
  GlobalState& operator=(const GlobalState& other) = delete;

  ~GlobalState();

  static GlobalState* GetInstance();

  static bool HasInstance();

  AdsClient& GetAdsClient();

  AdsNotifierManager& GetAdsNotifierManager();
  BrowserManager& GetBrowserManager();
  ClientStateManager& GetClientStateManager();
  TokenStateManager& GetTokenStateManager();
  DatabaseManager& GetDatabaseManager();
  DiagnosticManager& GetDiagnosticManager();
  AdHistoryManager& GetHistoryManager();
  NotificationAdManager& GetNotificationAdManager();
  TabManager& GetTabManager();
  UserActivityManager& GetUserActivityManager();
  AdsCore& GetAdsCore();

  mojom::SysInfo& SysInfo();
  mojom::BuildChannelInfo& BuildChannel();
  mojom::CommandLineSwitches& CommandLineSwitches();
  mojom::ContentSettings& ContentSettings();

  void PostDelayedTask(base::OnceClosure task, base::TimeDelta delay);

 private:
  void PostDelayedTaskCallback(base::OnceClosure task);

  SEQUENCE_CHECKER(sequence_checker_);

  const raw_ref<AdsClient> ads_client_;

  const std::unique_ptr<GlobalStateHolder> global_state_holder_;

  std::unique_ptr<AdsNotifierManager> ads_notifier_manager_;
  std::unique_ptr<BrowserManager> browser_manager_;
  std::unique_ptr<ClientStateManager> client_state_manager_;
  std::unique_ptr<TokenStateManager> token_state_manager_;
  std::unique_ptr<DatabaseManager> database_manager_;
  std::unique_ptr<DiagnosticManager> diagnostic_manager_;
  std::unique_ptr<AdHistoryManager> ad_history_manager_;
  std::unique_ptr<NotificationAdManager> notification_ad_manager_;
  std::unique_ptr<TabManager> tab_manager_;
  std::unique_ptr<UserActivityManager> user_activity_manager_;
  std::unique_ptr<AdsCore> ads_core_;

  mojom::SysInfo mojom_sys_info_;
  mojom::BuildChannelInfo mojom_build_channel_;
  mojom::CommandLineSwitches mojom_command_line_switches_;
  mojom::ContentSettings mojom_content_settings_;

  base::WeakPtrFactory<GlobalState> weak_ptr_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_GLOBAL_STATE_GLOBAL_STATE_H_
