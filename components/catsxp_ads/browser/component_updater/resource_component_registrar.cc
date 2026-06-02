/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component_registrar.h"

#include <ostream>
#include <string_view>

#include "base/check.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/component_info.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/component_util.h"
#include "catsxp/components/catsxp_ads/browser/component_updater/resource_component_registrar_delegate.h"

namespace catsxp_ads {

namespace {
constexpr std::string_view kComponentName = "Catsxp Ads Resources ($1)";
}  // namespace

ResourceComponentRegistrar::ResourceComponentRegistrar(
    Delegate* component_updater_delegate,
    ResourceComponentRegistrarDelegate& resource_component_registrar_delegate)
    : catsxp_component_updater::CatsxpComponent(component_updater_delegate),
      resource_component_registrar_delegate_(
          resource_component_registrar_delegate) {
  CHECK(component_updater_delegate);
}

ResourceComponentRegistrar::~ResourceComponentRegistrar() = default;

void ResourceComponentRegistrar::RegisterResourceComponent(
    const std::string& resource_id) {
  CHECK(!resource_id.empty());

  std::optional<ComponentInfo> component = GetComponent(resource_id);
  if (!component) {
    return VLOG(1) << "Ads resource not supported for " << resource_id;
  }

  if (resource_component_id_ && resource_component_id_ != component->id) {
    Unregister();
    OnComponentUnregistered(*resource_component_id_);
    last_install_dir_.reset();
  }
  resource_component_id_ = component->id;

  const std::string component_name =
      base::ReplaceStringPlaceholders(kComponentName, {resource_id}, nullptr);

  VLOG(1) << "Registering " << component_name << " with id "
          << *resource_component_id_;

  Register(component_name, *resource_component_id_,
           std::string(component->public_key_base64));

  if (last_install_dir_) {
    // The component was already ready before this registration. Replay
    // OnResourceComponentRegistered so that newly-added observers (e.g. a
    // profile opened after the component had already been processed) receive
    // the current resource metadata.
    resource_component_registrar_delegate_->OnResourceComponentRegistered(
        *resource_component_id_, *last_install_dir_);
  }
}

void ResourceComponentRegistrar::UnregisterResourceComponent() {
  if (!resource_component_id_) {
    return;
  }

  Unregister();
  OnComponentUnregistered(*resource_component_id_);
  last_install_dir_.reset();
  resource_component_id_.reset();
}

///////////////////////////////////////////////////////////////////////////////

void ResourceComponentRegistrar::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& /*resource*/) {
  last_install_dir_ = install_dir;
  resource_component_registrar_delegate_->OnResourceComponentRegistered(
      component_id, install_dir);
}

void ResourceComponentRegistrar::OnComponentUnregistered(
    const std::string& component_id) {
  resource_component_registrar_delegate_->OnResourceComponentUnregistered(
      component_id);
}

}  // namespace catsxp_ads
