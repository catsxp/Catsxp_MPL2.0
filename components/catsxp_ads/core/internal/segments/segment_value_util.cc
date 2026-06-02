/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/segments/segment_value_util.h"

#include <string>

#include "base/check.h"

namespace catsxp_ads {

base::ListValue SegmentsToList(const SegmentList& segments) {
  base::ListValue list;

  for (const auto& segment : segments) {
    CHECK(!segment.empty());
    list.Append(segment);
  }

  return list;
}

SegmentList SegmentsFromList(const base::ListValue& list) {
  SegmentList segments;
  segments.reserve(list.size());

  for (const auto& value : list) {
    if (!value.is_string()) {
      return {};
    }

    const std::string& segment = value.GetString();
    if (segment.empty()) {
      return {};
    }

    segments.push_back(segment);
  }

  return segments;
}

}  // namespace catsxp_ads
