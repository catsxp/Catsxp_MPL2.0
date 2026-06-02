/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MEDIA_DETECTOR_COMPONENT_INSTALLER_H_
#define CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MEDIA_DETECTOR_COMPONENT_INSTALLER_H_

#include "base/files/file_path.h"
#include "base/functional/callback.h"

namespace component_updater {
class ComponentUpdateService;
}  // namespace component_updater

namespace playlist {

using OnComponentReadyCallback =
    base::RepeatingCallback<void(const base::FilePath& install_path)>;

void RegisterMediaDetectorComponent(
    component_updater::ComponentUpdateService* cus,
    OnComponentReadyCallback callback);

}  // namespace playlist

#endif  // CATSXP_COMPONENTS_PLAYLIST_CONTENT_BROWSER_MEDIA_DETECTOR_COMPONENT_INSTALLER_H_
