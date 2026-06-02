/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_user_model_segments.h"

#include <cstddef>

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_segments.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/segments/top_user_model_segments_util.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

namespace catsxp_ads {

namespace {

constexpr size_t kTopSegmentsMaxCount = 3;

constexpr size_t kTopIntentSegmentsMaxCount = 3;
constexpr size_t kTopLatentInterestSegmentsMaxCount = 3;
constexpr size_t kTopInterestSegmentsMaxCount = 3;

}  // namespace

SegmentList GetTopChildSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model, kTopSegmentsMaxCount,
                        /*parent_only=*/false);
}

SegmentList GetTopParentSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model, kTopSegmentsMaxCount,
                        /*parent_only=*/true);
}

SegmentList GetTopChildIntentSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model.intent.segments, kTopIntentSegmentsMaxCount,
                        /*parent_only=*/false);
}

SegmentList GetTopParentIntentSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model.intent.segments, kTopIntentSegmentsMaxCount,
                        /*parent_only=*/true);
}

SegmentList GetTopChildLatentInterestSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model.latent_interest.segments,
                        kTopLatentInterestSegmentsMaxCount,
                        /*parent_only=*/false);
}

SegmentList GetTopParentLatentInterestSegments(
    const UserModelInfo& user_model) {
  return GetTopSegments(user_model.latent_interest.segments,
                        kTopLatentInterestSegmentsMaxCount,
                        /*parent_only=*/true);
}

SegmentList GetTopChildInterestSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model.interest.segments,
                        kTopInterestSegmentsMaxCount,
                        /*parent_only=*/false);
}

SegmentList GetTopParentInterestSegments(const UserModelInfo& user_model) {
  return GetTopSegments(user_model.interest.segments,
                        kTopInterestSegmentsMaxCount,
                        /*parent_only=*/true);
}

}  // namespace catsxp_ads
