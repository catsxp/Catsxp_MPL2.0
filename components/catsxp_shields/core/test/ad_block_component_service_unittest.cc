/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include <algorithm>

#include "catsxp/components/catsxp_shields/core/browser/filter_list_catalog_entry.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(AdBlockComponentServiceTest, UserModelLanguages) {
  std::vector<catsxp_shields::FilterListCatalogEntry> catalog;
  catalog.push_back(catsxp_shields::FilterListCatalogEntry(
      "uuid", "https://catsxp.com", "Testing Filter List #1", {"fr"},
      "https://www.catsxp.com", "Filter list for testing purposes", false,
      false, false, 0, {}, "componentid", "base64publickey"));
  catalog.push_back(catsxp_shields::FilterListCatalogEntry(
      "uuid", "https://catsxp.com", "Testing Filter List #2", {"en"},
      "https://www.catsxp.com", "Filter list for testing purposes", false,
      false, false, 0, {}, "componentid", "base64publickey"));
  catalog.push_back(catsxp_shields::FilterListCatalogEntry(
      "uuid", "https://catsxp.com", "Testing Filter List #2", {"fr"},
      "https://www.catsxp.com", "Filter list for testing purposes", false,
      false, false, 0, {}, "componentid", "base64publickey"));

  std::vector<std::string> languages({"fr", "fR", "fr-FR", "fr-ca"});
  std::for_each(
      languages.begin(), languages.end(), [&](const std::string& language) {
        EXPECT_EQ(
            catsxp_shields::FindAdBlockFilterListsByLocale(catalog, language)
                .size(),
            2UL);
      });

  EXPECT_EQ(catsxp_shields::FindAdBlockFilterListsByLocale(catalog, "en").size(),
            1UL);

  EXPECT_EQ(catsxp_shields::FindAdBlockFilterListsByLocale(catalog, "is").size(),
            0UL);
}

TEST(AdBlockComponentServiceTest, MissingFieldDefaultValues) {
  auto catalog = catsxp_shields::FilterListCatalogFromJSON(R"([{
      "uuid": "uuid",
      "title": "Test list",
      "desc": "Just used for testing",
      "langs": [],
      "component_id": "componentid",
      "base64_public_key": "base64publickey",
      "list_text_component": {
          "component_id": "componentid",
          "base64_public_key": "base64publickey"
      },
      "sources": [
          {
              "url": "https://example.com",
              "format": "Standard",
              "support_url": "https://support.example.com"
          }
      ]
  }])");

  ASSERT_EQ(catalog.size(), 1UL);
  ASSERT_EQ(catalog[0].hidden, false);
  ASSERT_EQ(catalog[0].default_enabled, false);
  ASSERT_EQ(catalog[0].first_party_protections, false);
  ASSERT_EQ(catalog[0].permission_mask, 0);
  ASSERT_EQ(catalog[0].platforms.size(), 0UL);
}
