/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/playlist/content/browser/media_detector_component_installer.h"

#include <memory>
#include <string>
#include <vector>

#include "base/base64.h"
#include "base/containers/to_vector.h"
#include "base/functional/bind.h"
#include "base/functional/callback.h"
#include "catsxp/components/catsxp_component_updater/browser/catsxp_on_demand_updater.h"
#include "components/component_updater/component_installer.h"
#include "components/component_updater/component_updater_service.h"
#include "crypto/sha2.h"

using catsxp_component_updater::CatsxpOnDemandUpdater;

namespace playlist {

namespace {

constexpr char kComponentID[] = "mjcibdkidjfcnepjimbembimffigphba";

class MediaDetectorComponentInstallerPolicy
    : public component_updater::ComponentInstallerPolicy {
 public:
  explicit MediaDetectorComponentInstallerPolicy(
      OnComponentReadyCallback callback);
  ~MediaDetectorComponentInstallerPolicy() override;

  MediaDetectorComponentInstallerPolicy(
      const MediaDetectorComponentInstallerPolicy&) = delete;
  MediaDetectorComponentInstallerPolicy& operator=(
      const MediaDetectorComponentInstallerPolicy&) = delete;

  // component_updater::ComponentInstallerPolicy
  bool SupportsGroupPolicyEnabledComponentUpdates() const override;
  bool RequiresNetworkEncryption() const override;
  update_client::CrxInstaller::Result OnCustomInstall(
      const base::DictValue& manifest,
      const base::FilePath& install_dir) override;
  void OnCustomUninstall() override;
  bool VerifyInstallation(const base::DictValue& manifest,
                          const base::FilePath& install_dir) const override;
  void ComponentReady(const base::Version& version,
                      const base::FilePath& path,
                      base::DictValue manifest) override;
  base::FilePath GetRelativeInstallDir() const override;
  void GetHash(std::vector<uint8_t>* hash) const override;
  std::string GetName() const override;
  update_client::InstallerAttributes GetInstallerAttributes() const override;
  bool IsCatsxpComponent() const override;

 private:
  OnComponentReadyCallback ready_callback_;
  std::array<uint8_t, crypto::kSHA256Length> component_hash_;
};

MediaDetectorComponentInstallerPolicy::MediaDetectorComponentInstallerPolicy(
    OnComponentReadyCallback callback)
    : ready_callback_(callback) {
  // Generate hash from public key.
  constexpr char kComponentPublicKey[] =
      "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAw6oSNp4B+QZAbRVObwxy"
      "yKZxP/ZHou3ZnnNpYhplO+rKO44mPJuypk7vE5wCR2K4L9H6Uh96+LNi1zF961QR"
      "pWxjf4vpxxsRjFis/HfRNDZ4wonY0f8/ThYalZMdhBMp8Cf0RTXiMO+sIPnjqvgu"
      "otEivtASzaV8PVEzax8pPIVe6I0tg5YudOm/fzhNu/4e4Cmcas5+gZWloZgItkUH"
      "WRga9lfcGc/ec1elm8lnPoTVmoUYYTKF35+jMcL2sUak23IBf88p6/Worhyn5az6"
      "aYaolu5fRqPyAPh9FVGk2t1VqxbYA1UiF3gPl/cyAz6KwItKcecD9xGDLK+PSQh7"
      "gQIDAQAB";

  auto decoded_public_key = base::Base64Decode(kComponentPublicKey);
  CHECK(decoded_public_key);
  component_hash_ = crypto::SHA256Hash(*decoded_public_key);
}

MediaDetectorComponentInstallerPolicy::
    ~MediaDetectorComponentInstallerPolicy() = default;

bool MediaDetectorComponentInstallerPolicy::
    SupportsGroupPolicyEnabledComponentUpdates() const {
  return true;
}

bool MediaDetectorComponentInstallerPolicy::RequiresNetworkEncryption() const {
  return false;
}

update_client::CrxInstaller::Result
MediaDetectorComponentInstallerPolicy::OnCustomInstall(
    const base::DictValue& manifest,
    const base::FilePath& install_dir) {
  return update_client::CrxInstaller::Result(0);
}

void MediaDetectorComponentInstallerPolicy::OnCustomUninstall() {}

void MediaDetectorComponentInstallerPolicy::ComponentReady(
    const base::Version& version,
    const base::FilePath& path,
    base::DictValue manifest) {
  ready_callback_.Run(path);
}

bool MediaDetectorComponentInstallerPolicy::VerifyInstallation(
    const base::DictValue& manifest,
    const base::FilePath& install_dir) const {
  return true;
}

base::FilePath MediaDetectorComponentInstallerPolicy::GetRelativeInstallDir()
    const {
  return base::FilePath::FromUTF8Unsafe(kComponentID);
}

void MediaDetectorComponentInstallerPolicy::GetHash(
    std::vector<uint8_t>* hash) const {
  *hash = base::ToVector(component_hash_);
}

std::string MediaDetectorComponentInstallerPolicy::GetName() const {
  return "playlist-component";
}

update_client::InstallerAttributes
MediaDetectorComponentInstallerPolicy::GetInstallerAttributes() const {
  return update_client::InstallerAttributes();
}

bool MediaDetectorComponentInstallerPolicy::IsCatsxpComponent() const {
  return true;
}

void OnRegisteredToComponentUpdateService() {
  CatsxpOnDemandUpdater::GetInstance()->EnsureInstalled(kComponentID);
}

}  // namespace

void RegisterMediaDetectorComponent(
    component_updater::ComponentUpdateService* cus,
    OnComponentReadyCallback callback) {
  // In test, |cus| could be nullptr.
  if (!cus ||
      CatsxpOnDemandUpdater::GetInstance()->is_component_update_disabled()) {
    return;
  }

  auto installer = base::MakeRefCounted<component_updater::ComponentInstaller>(
      std::make_unique<MediaDetectorComponentInstallerPolicy>(callback));
  installer->Register(cus,
                      base::BindOnce(OnRegisteredToComponentUpdateService));
}

}  // namespace playlist
