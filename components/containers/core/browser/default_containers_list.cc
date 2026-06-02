/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/containers/core/browser/default_containers_list.h"

#include "catsxp/ui/color/nala/nala_color_id.h"
#include "components/grit/catsxp_components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/color/color_provider.h"
#include "ui/color/color_provider_manager.h"

namespace containers {

std::vector<mojom::ContainerPtr> CreateDefaultContainersList() {
  const auto* color_provider =
      ui::ColorProviderManager::Get().GetColorProviderFor(
          ui::ColorProviderKey());
  CHECK(color_provider);

  std::vector<mojom::ContainerPtr> default_containers;

  default_containers.push_back(mojom::Container::New(
      kDefaultContainerIds[0],
      l10n_util::GetStringUTF8(IDS_CONTAINERS_DEFAULT_PERSONAL_NAME),
      mojom::Icon::kPersonal,
      color_provider->GetColor(nala::kColorPrimitiveBlue60)));
  default_containers.push_back(mojom::Container::New(
      kDefaultContainerIds[1],
      l10n_util::GetStringUTF8(IDS_CONTAINERS_DEFAULT_WORK_NAME),
      mojom::Icon::kWork,
      color_provider->GetColor(nala::kColorPrimitiveRed60)));
  default_containers.push_back(mojom::Container::New(
      kDefaultContainerIds[2],
      l10n_util::GetStringUTF8(IDS_CONTAINERS_DEFAULT_SOCIAL_NAME),
      mojom::Icon::kSocial,
      color_provider->GetColor(nala::kColorPrimitivePurple60)));
  default_containers.push_back(mojom::Container::New(
      kDefaultContainerIds[3],
      l10n_util::GetStringUTF8(IDS_CONTAINERS_DEFAULT_SCHOOL_NAME),
      mojom::Icon::kSchool,
      color_provider->GetColor(nala::kColorPrimitiveGreen60)));

  DCHECK_EQ(default_containers.size(), kDefaultContainerIds.size());

  return default_containers;
}

}  // namespace containers
