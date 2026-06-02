/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_DELEGATE_H_
#define CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_DELEGATE_H_

#include <memory>
#include <string>

#include "base/functional/callback.h"
#include "base/functional/callback_helpers.h"
#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "catsxp/components/ntp_background_images/browser/catsxp_ntp_custom_background_service.h"

class CustomBackgroundFileManager;
class Profile;

class CatsxpNTPCustomBackgroundServiceDelegate
    : public ntp_background_images::CatsxpNTPCustomBackgroundService::Delegate {
 public:
  explicit CatsxpNTPCustomBackgroundServiceDelegate(Profile* profile);
  ~CatsxpNTPCustomBackgroundServiceDelegate() override;
  CatsxpNTPCustomBackgroundServiceDelegate(
      const CatsxpNTPCustomBackgroundServiceDelegate&) = delete;
  CatsxpNTPCustomBackgroundServiceDelegate& operator=(
      const CatsxpNTPCustomBackgroundServiceDelegate&) = delete;

 private:
  FRIEND_TEST_ALL_PREFIXES(CatsxpNTPCustomBackgroundServiceDelegateUnitTest,
                           MigrationSuccess);
  FRIEND_TEST_ALL_PREFIXES(CatsxpNTPCustomBackgroundServiceDelegateUnitTest,
                           MigrationFail);

  bool ShouldMigrateCustomImagePref() const;
  void MigrateCustomImage(
      base::OnceCallback<void(bool)> callback = base::DoNothing());

  // CatsxpNTPCustomBackgroundService::Delegate overrides:
  bool IsCustomImageBackgroundEnabled() const override;
  base::FilePath GetCustomBackgroundImageLocalFilePath(
      const GURL& url) const override;
  GURL GetCustomBackgroundImageURL() const override;
  bool IsColorBackgroundEnabled() const override;
  std::string GetColor() const override;
  bool ShouldUseRandomValue() const override;
  bool HasPreferredCatsxpBackground() const override;
  base::DictValue GetPreferredCatsxpBackground() const override;

  raw_ptr<Profile> profile_ = nullptr;

  std::unique_ptr<CustomBackgroundFileManager> file_manager_;
};

#endif  // CATSXP_BROWSER_NTP_BACKGROUND_CATSXP_NTP_CUSTOM_BACKGROUND_SERVICE_DELEGATE_H_
