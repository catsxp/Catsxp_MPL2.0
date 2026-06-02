/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/ad_units/new_tab_page_ad/new_tab_page_ad_event_type_util.h"

#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsNewTabPageAdEventTypeUtilTest, ToMojomNewTabPageAdEventType) {
  // Act & Assert
  EXPECT_EQ(ToMojomNewTabPageAdEventType("served"),
            mojom::NewTabPageAdEventType::kServedImpression);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("view"),
            mojom::NewTabPageAdEventType::kViewedImpression);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("click"),
            mojom::NewTabPageAdEventType::kClicked);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("interaction"),
            mojom::NewTabPageAdEventType::kInteraction);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("media_play"),
            mojom::NewTabPageAdEventType::kMediaPlay);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("media_25"),
            mojom::NewTabPageAdEventType::kMedia25);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("media_100"),
            mojom::NewTabPageAdEventType::kMedia100);

  EXPECT_EQ(ToMojomNewTabPageAdEventType(""), std::nullopt);

  EXPECT_EQ(ToMojomNewTabPageAdEventType("foobar"), std::nullopt);
}

TEST(CatsxpAdsNewTabPageAdEventTypeUtilTest, ToString) {
  // Act & Assert
  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kServedImpression),
            "served");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kViewedImpression), "view");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kClicked), "click");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kInteraction),
            "interaction");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kMediaPlay), "media_play");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kMedia25), "media_25");

  EXPECT_EQ(ToString(mojom::NewTabPageAdEventType::kMedia100), "media_100");
}

}  // namespace catsxp_ads
