/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/ntp_background/catsxp_ntp_custom_background_service_delegate.h"

#include <algorithm>
#include <utility>

#include "base/check.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "catsxp/browser/catsxp_browser_process.h"
#include "catsxp/browser/ntp_background/constants.h"
#include "catsxp/browser/ntp_background/custom_background_file_manager.h"
#include "catsxp/browser/ntp_background/ntp_background_prefs.h"
#include "catsxp/components/constants/pref_names.h"
#include "catsxp/components/ntp_background_images/browser/ntp_background_images_data.h"
#include "catsxp/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "catsxp/components/ntp_background_images/browser/url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/themes/theme_syncable_service.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/url_constants.h"
#include "components/prefs/pref_service.h"
#include "url/gurl.h"

CatsxpNTPCustomBackgroundServiceDelegate::
    CatsxpNTPCustomBackgroundServiceDelegate(Profile* profile)
    : profile_(profile),
      file_manager_(std::make_unique<CustomBackgroundFileManager>(profile_)) {
  if (ShouldMigrateCustomImagePref()) {
    DVLOG(2) << "Migrate old custom background image";

    MigrateCustomImage();
  }
}

CatsxpNTPCustomBackgroundServiceDelegate::
    ~CatsxpNTPCustomBackgroundServiceDelegate() = default;

bool CatsxpNTPCustomBackgroundServiceDelegate::ShouldMigrateCustomImagePref()
    const {
  auto prefs = NTPBackgroundPrefs(profile_->GetPrefs());
  return prefs.IsCustomImageType() && prefs.GetCustomImageList().empty();
}

void CatsxpNTPCustomBackgroundServiceDelegate::MigrateCustomImage(
    base::OnceCallback<void(bool)> callback) {
  auto prefs = NTPBackgroundPrefs(profile_->GetPrefs());
  file_manager_->MoveImage(
      base::FilePath(profile_->GetPath().AppendASCII(
          ntp_background_images::kSanitizedImageFileNameDeprecated)),
      base::BindOnce(
          [](Profile* profile, bool result) {
            auto prefs = NTPBackgroundPrefs(profile->GetPrefs());
            if (!result) {
              LOG(ERROR) << "Failed to migrate Custom background image. "
                            "Resets to default background";
              prefs.SetType(NTPBackgroundPrefs::Type::kCatsxp);
              prefs.SetShouldUseRandomValue(true);
              prefs.SetSelectedValue(std::string());
              return false;
            }

            prefs.SetSelectedValue(
                ntp_background_images::kSanitizedImageFileNameDeprecated);
            prefs.AddCustomImageToList(
                ntp_background_images::kSanitizedImageFileNameDeprecated);
            return true;
          },
          profile_)
          .Then(std::move(callback)));
}

bool CatsxpNTPCustomBackgroundServiceDelegate::IsCustomImageBackgroundEnabled()
    const {
  if (profile_->GetPrefs()->IsManagedPreference(
          prefs::kNtpCustomBackgroundDict)) {
    return false;
  }

  return NTPBackgroundPrefs(profile_->GetPrefs()).IsCustomImageType();
}

base::FilePath
CatsxpNTPCustomBackgroundServiceDelegate::GetCustomBackgroundImageLocalFilePath(
    const GURL& url) const {
  return CustomBackgroundFileManager::Converter(url, file_manager_.get())
      .To<base::FilePath>();
}

GURL CatsxpNTPCustomBackgroundServiceDelegate::GetCustomBackgroundImageURL()
    const {
  DCHECK(IsCustomImageBackgroundEnabled());

  auto prefs = NTPBackgroundPrefs(profile_->GetPrefs());
  auto name = prefs.GetSelectedValue();
  return CustomBackgroundFileManager::Converter(name).To<GURL>();
}

bool CatsxpNTPCustomBackgroundServiceDelegate::IsColorBackgroundEnabled() const {
  return NTPBackgroundPrefs(profile_->GetPrefs()).IsColorType();
}

std::string CatsxpNTPCustomBackgroundServiceDelegate::GetColor() const {
  if (!IsColorBackgroundEnabled()) {
    return {};
  }

  const auto selected_value =
      NTPBackgroundPrefs(profile_->GetPrefs()).GetSelectedValue();
  return selected_value;
}

bool CatsxpNTPCustomBackgroundServiceDelegate::ShouldUseRandomValue() const {
  return NTPBackgroundPrefs(profile_->GetPrefs()).ShouldUseRandomValue();
}

bool CatsxpNTPCustomBackgroundServiceDelegate::HasPreferredCatsxpBackground()
    const {
  const auto pref = NTPBackgroundPrefs(profile_->GetPrefs());
  if (!pref.IsCatsxpType() || pref.ShouldUseRandomValue()) {
    return false;
  }

  auto selected_value = pref.GetSelectedValue();
  return GURL(selected_value).is_valid();
}

base::DictValue
CatsxpNTPCustomBackgroundServiceDelegate::GetPreferredCatsxpBackground() const {
  DCHECK(HasPreferredCatsxpBackground());

  auto pref = NTPBackgroundPrefs(profile_->GetPrefs());
  const auto selected_value = pref.GetSelectedValue();
  const auto image_url = GURL(selected_value);

  const auto* service =
      g_catsxp_browser_process->ntp_background_images_service();
  DCHECK(service);

  auto* image_data = service->GetBackgroundImagesData();
  if (!image_data) {
    // This can happen when the image data is not downloaded yet.
    return {};
  }

  auto iter = std::ranges::find_if(
      image_data->backgrounds,
      [image_data, &image_url](const auto& background) {
        return image_data->url_prefix +
                   background.file_path.BaseName().AsUTF8Unsafe() ==
               image_url.spec();
      });

  if (iter == image_data->backgrounds.end()) {
    // Due to version update, the data could have been invalidated.
    // Try fixing up the data and return empty value.
    pref.SetShouldUseRandomValue(true);
    pref.SetSelectedValue(base::EmptyString());
    return {};
  }

  return image_data->GetBackgroundAt(
      std::distance(image_data->backgrounds.begin(), iter));
}
