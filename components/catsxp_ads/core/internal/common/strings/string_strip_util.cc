/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/common/strings/string_strip_util.h"

#include "base/check.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "third_party/re2/src/re2/re2.h"

namespace catsxp_ads {

namespace {

std::string Strip(const std::string& value, const std::string& pattern) {
  CHECK(!pattern.empty());

  if (value.empty()) {
    return {};
  }

  std::string stripped_value(value);

  RE2::GlobalReplace(&stripped_value, pattern, " ");

  std::u16string stripped_value_string16 = base::UTF8ToUTF16(stripped_value);

  stripped_value_string16 = base::CollapseWhitespace(
      stripped_value_string16, /*trim_sequences_with_line_breaks=*/true);

  return base::UTF16ToUTF8(stripped_value_string16);
}

}  // namespace

std::string StripNonAlphaCharacters(const std::string& value) {
  const std::string escaped_characters =
      RE2::QuoteMeta("!\"#$%&'()*+,-./:<=>?@\\[]^_`{|}~");

  const std::string pattern = base::ReplaceStringPlaceholders(
      "[[:cntrl:]]|\\\\(t|n|v|f|r)|[\\t\\n\\v\\f\\r]|\\\\x[[:xdigit:]][[:"
      "xdigit:]]|[$1]|\\S*\\d+\\S*",
      {escaped_characters}, nullptr);

  return Strip(value, pattern);
}

std::string StripNonAlphaNumericCharacters(const std::string& value) {
  const std::string escaped_characters =
      RE2::QuoteMeta("!\"#$%&'()*+,-./:<=>?@\\[]^_`{|}~");

  const std::string pattern = base::ReplaceStringPlaceholders(
      "[[:cntrl:]]|\\\\(t|n|v|f|r)|[\\t\\n\\v\\f\\r]|\\\\x[[:xdigit:]][[:"
      "xdigit:]]|[$1]",
      {escaped_characters}, nullptr);

  return Strip(value, pattern);
}

}  // namespace catsxp_ads
