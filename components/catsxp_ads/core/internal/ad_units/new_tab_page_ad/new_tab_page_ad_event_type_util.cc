/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/new_tab_page_ad/new_tab_page_ad_event_type_util.h"

#include "base/containers/fixed_flat_map.h"
#include "base/containers/map_util.h"
#include "base/types/optional_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"

namespace catsxp_ads {

namespace {

constexpr std::string_view kServedImpressionAdEventType = "served";
constexpr std::string_view kViewedImpressionAdEventType = "view";
constexpr std::string_view kClickedAdEventType = "click";
constexpr std::string_view kInteractionAdEventType = "interaction";
constexpr std::string_view kMediaPlayAdEventType = "media_play";
constexpr std::string_view kMedia25AdEventType = "media_25";
constexpr std::string_view kMedia100AdEventType = "media_100";

constexpr auto kStringToMojomMap =
    base::MakeFixedFlatMap<std::string_view, mojom::NewTabPageAdEventType>({
        {kServedImpressionAdEventType,
         mojom::NewTabPageAdEventType::kServedImpression},
        {kViewedImpressionAdEventType,
         mojom::NewTabPageAdEventType::kViewedImpression},
        {kClickedAdEventType, mojom::NewTabPageAdEventType::kClicked},
        {kInteractionAdEventType, mojom::NewTabPageAdEventType::kInteraction},
        {kMediaPlayAdEventType, mojom::NewTabPageAdEventType::kMediaPlay},
        {kMedia25AdEventType, mojom::NewTabPageAdEventType::kMedia25},
        {kMedia100AdEventType, mojom::NewTabPageAdEventType::kMedia100},
    });

}  // namespace

std::optional<mojom::NewTabPageAdEventType> ToMojomNewTabPageAdEventType(
    std::string_view value) {
  return base::OptionalFromPtr(base::FindOrNull(kStringToMojomMap, value));
}

std::string_view ToString(mojom::NewTabPageAdEventType value) {
  switch (value) {
    case mojom::NewTabPageAdEventType::kServedImpression:
      return kServedImpressionAdEventType;
    case mojom::NewTabPageAdEventType::kViewedImpression:
      return kViewedImpressionAdEventType;
    case mojom::NewTabPageAdEventType::kClicked:
      return kClickedAdEventType;
    case mojom::NewTabPageAdEventType::kInteraction:
      return kInteractionAdEventType;
    case mojom::NewTabPageAdEventType::kMediaPlay:
      return kMediaPlayAdEventType;
    case mojom::NewTabPageAdEventType::kMedia25:
      return kMedia25AdEventType;
    case mojom::NewTabPageAdEventType::kMedia100:
      return kMedia100AdEventType;
  }
}

}  // namespace catsxp_ads
