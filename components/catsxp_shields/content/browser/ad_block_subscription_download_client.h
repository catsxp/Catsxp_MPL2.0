/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_DOWNLOAD_CLIENT_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_DOWNLOAD_CLIENT_H_

#include <string>
#include <vector>

#include "base/functional/callback.h"
#include "components/download/public/background_service/client.h"
#include "components/download/public/background_service/download_metadata.h"

namespace catsxp_shields {

class AdBlockSubscriptionServiceManager;

class AdBlockSubscriptionDownloadManager;

class AdBlockSubscriptionDownloadClient : public download::Client {
 public:
  using SubscriptionServiceManagerGetter =
      base::RepeatingCallback<AdBlockSubscriptionServiceManager*()>;

  explicit AdBlockSubscriptionDownloadClient(
      SubscriptionServiceManagerGetter subscription_manager_getter);
  ~AdBlockSubscriptionDownloadClient() override;
  AdBlockSubscriptionDownloadClient(const AdBlockSubscriptionDownloadClient&) =
      delete;
  AdBlockSubscriptionDownloadClient& operator=(
      const AdBlockSubscriptionDownloadClient&) = delete;

  // download::Client:
  void OnServiceInitialized(
      bool state_lost,
      const std::vector<download::DownloadMetaData>& downloads) override;
  void OnServiceUnavailable() override;
  void OnDownloadFailed(const std::string& guid,
                        const download::CompletionInfo& completion_info,
                        download::Client::FailureReason reason) override;
  void OnDownloadSucceeded(
      const std::string& guid,
      const download::CompletionInfo& completion_info) override;
  bool CanServiceRemoveDownloadedFile(const std::string& guid,
                                      bool force_delete) override;
  void GetUploadData(const std::string& guid,
                     download::GetUploadDataCallback callback) override;

 private:
  // Returns the AdBlockSubscriptionDownloadManager for the profile.
  AdBlockSubscriptionDownloadManager* GetAdBlockSubscriptionDownloadManager();

  SubscriptionServiceManagerGetter subscription_manager_getter_;
};

}  // namespace catsxp_shields

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_CONTENT_BROWSER_AD_BLOCK_SUBSCRIPTION_DOWNLOAD_CLIENT_H_
