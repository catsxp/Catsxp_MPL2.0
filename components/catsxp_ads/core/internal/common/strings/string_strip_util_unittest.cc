/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_strip_util.h"

#include <string>

#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- catsxp_unit_tests --filter=CatsxpAds*

namespace catsxp_ads {

TEST(CatsxpAdsStringStripUtilTest, StripNonAlphaCharactersFromEmptyContent) {
  // Act & Assert
  EXPECT_THAT(StripNonAlphaCharacters(""), ::testing::IsEmpty());
}

TEST(CatsxpAdsStringStripUtilTest, StripNonAlphaCharactersFromWhitespace) {
  // Act & Assert
  EXPECT_THAT(StripNonAlphaCharacters("   "), ::testing::IsEmpty());
}

TEST(CatsxpAdsStringStripUtilTest, StripNonAlphaCharacters) {
  // Arrange
  const std::string content =
      "  The quick brown fox jumps over the lazy dog. "
      "$123,000.0 !\"#$%&'()*+,-./:<=>?@\\[]^_`{|}~ 0123456789 \t\n\v\f\r "
      "0x7F x123x a1b2c3 Les naïfs ægithales hâtifs pondant à Noël où il "
      "gèle sont sûrs d'être déçus en voyant leurs drôles d'œufs abîmés. "
      "Falsches Üben von Xylophonmusik quält jeden größeren Zwerg. ξεσκεπάζω "
      "την ψυχοφθόρα \\t\\n\\v\\f\\r βδελυγμία. いろはにほへど　ちりぬるを "
      "わがよたれぞ　つねならむ うゐのおくやま　けふこえて あさきゆめみじ　"
      "ゑひもせず  ";  // The Quick Brown Fox... Pangrams

  // Act
  const std::string stripped_content = StripNonAlphaCharacters(content);

  // Assert
  const std::string expected_stripped_content =
      "The quick brown fox jumps over the lazy dog Les naïfs ægithales hâtifs "
      "pondant à Noël où il gèle sont sûrs d être déçus en voyant leurs drôles "
      "d œufs abîmés Falsches Üben von Xylophonmusik quält jeden größeren "
      "Zwerg ξεσκεπάζω την ψυχοφθόρα βδελυγμία いろはにほへど ちりぬるを "
      "わがよたれぞ つねならむ うゐのおくやま けふこえて あさきゆめみじ "
      "ゑひもせず";
  EXPECT_EQ(expected_stripped_content, stripped_content);
}

TEST(CatsxpAdsStringStripUtilTest,
     StripNonAlphaNumericCharactersFromEmptyContent) {
  // Act & Assert
  EXPECT_THAT(StripNonAlphaNumericCharacters(""), ::testing::IsEmpty());
}

TEST(CatsxpAdsStringStripUtilTest,
     StripNonAlphaNumericCharactersFromWhitespace) {
  // Act & Assert
  EXPECT_THAT(StripNonAlphaNumericCharacters("   "), ::testing::IsEmpty());
}

TEST(CatsxpAdsStringStripUtilTest, StripNonAlphaNumericCharacters) {
  // Arrange
  const std::string content =
      "  The quick brown fox jumps over the lazy dog. "
      "$123,000.0 !\"#$%&'()*+,-./:<=>?@\\[]^_`{|}~ 0123456789 \t\n\v\f\r "
      "0x7F x123x a1b2c3 Les naïfs ægithales hâtifs pondant à Noël où il "
      "gèle sont sûrs d'être déçus en voyant leurs drôles d'œufs abîmés. "
      "Falsches Üben von Xylophonmusik quält jeden größeren Zwerg. ξεσκεπάζω "
      "την ψυχοφθόρα \\t\\n\\v\\f\\r βδελυγμία. いろはにほへど　ちりぬるを "
      "わがよたれぞ　つねならむ うゐのおくやま　けふこえて あさきゆめみじ　"
      "ゑひもせず  ";  // The Quick Brown Fox... Pangrams

  // Act
  const std::string stripped_content = StripNonAlphaNumericCharacters(content);

  // Assert
  const std::string expected_stripped_content =
      "The quick brown fox jumps over the lazy dog 123 000 0 0123456789 0x7F "
      "x123x a1b2c3 Les naïfs ægithales hâtifs pondant à Noël où il gèle sont "
      "sûrs d être déçus en voyant leurs drôles d œufs abîmés Falsches Üben "
      "von Xylophonmusik quält jeden größeren Zwerg ξεσκεπάζω την ψυχοφθόρα "
      "βδελυγμία いろはにほへど ちりぬるを わがよたれぞ つねならむ "
      "うゐのおくやま けふこえて あさきゆめみじ ゑひもせず";
  EXPECT_EQ(expected_stripped_content, stripped_content);
}

}  // namespace catsxp_ads
