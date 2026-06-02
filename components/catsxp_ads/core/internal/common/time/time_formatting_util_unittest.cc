/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/time/time_formatting_util.h"

#include "base/test/icu_test_util.h"
#include "base/time/time.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/scoped_timezone_for_testing.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/test_base.h"
#include "catsxp/components/catsxp_ads/core/internal/common/test/time_test_util.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

class CatsxpAdsTimeFormattingUtilTest : public test::TestBase {};

TEST_F(CatsxpAdsTimeFormattingUtilTest,
       LongFriendlyDateAndTimeWithSentenceStyle) {
  // Arrange
  const base::test::ScopedRestoreICUDefaultLocale scoped_locale("en-US");
  const test::ScopedTimezoneForTesting scoped_timezone("UTC");
  const base::Time time = test::TimeFromUTCString("November 18 2020 14:30:00");

  // Act & Assert
  EXPECT_EQ("on Wednesday, November 18, 2020 at 2:30:00\xE2\x80\xAFPM",
            LongFriendlyDateAndTime(time));
}

TEST_F(CatsxpAdsTimeFormattingUtilTest,
       LongFriendlyDateAndTimeWithoutSentenceStyle) {
  // Arrange
  const base::test::ScopedRestoreICUDefaultLocale scoped_locale("en-US");
  const test::ScopedTimezoneForTesting scoped_timezone("UTC");
  const base::Time time = test::TimeFromUTCString("November 18 2020 14:30:00");

  // Act & Assert
  EXPECT_EQ("Wednesday, November 18, 2020 at 2:30:00\xE2\x80\xAFPM",
            LongFriendlyDateAndTime(time, /*use_sentence_style=*/false));
}

TEST_F(CatsxpAdsTimeFormattingUtilTest, FriendlyDateAndTimeWithSentenceStyle) {
  // Arrange
  const base::test::ScopedRestoreICUDefaultLocale scoped_locale("en-US");
  const test::ScopedTimezoneForTesting scoped_timezone("UTC");
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 14:30:00"));

  // Act & Assert
  EXPECT_EQ("on Friday, November 20, 2020 at 2:30:00\xE2\x80\xAFPM",
            FriendlyDateAndTime(
                test::TimeFromUTCString("November 20 2020 14:30:00")));
}

TEST_F(CatsxpAdsTimeFormattingUtilTest,
       FriendlyDateAndTimeWithoutSentenceStyle) {
  // Arrange
  const base::test::ScopedRestoreICUDefaultLocale scoped_locale("en-US");
  const test::ScopedTimezoneForTesting scoped_timezone("UTC");
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 14:30:00"));

  // Act & Assert
  EXPECT_EQ(
      "Friday, November 20, 2020 at 2:30:00\xE2\x80\xAFPM",
      FriendlyDateAndTime(test::TimeFromUTCString("November 20 2020 14:30:00"),
                          /*use_sentence_style=*/false));
}

TEST_F(CatsxpAdsTimeFormattingUtilTest, TimeToPrivacyPreservingIso8601) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 23:45:12.345"));

  // Act & Assert
  EXPECT_EQ("2020-11-18T23:00:00.000Z",
            TimeToPrivacyPreservingIso8601(test::Now()));
}

}  // namespace catsxp_ads
