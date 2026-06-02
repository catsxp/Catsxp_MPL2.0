/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_builder.h"

#include <memory>
#include <utility>

#include "base/barrier_closure.h"
#include "base/check.h"
#include "base/functional/bind.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_segments.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_segments.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_segments.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"
#include "catsxp/components/catsxp_ads/core/internal/serving/targeting/user_model/user_model_info.h"

namespace catsxp_ads {

namespace {

void BuildIntentSegmentsCallback(UserModelInfo* const user_model,
                                 base::OnceClosure barrier_closure,
                                 const SegmentList& segments) {
  CHECK(user_model);

  user_model->intent.segments = segments;
  std::move(barrier_closure).Run();
}

void BuildLatentInterestSegmentsCallback(UserModelInfo* const user_model,
                                         base::OnceClosure barrier_closure,
                                         const SegmentList& segments) {
  CHECK(user_model);

  user_model->latent_interest.segments = segments;
  std::move(barrier_closure).Run();
}

void BuildInterestSegmentsCallback(UserModelInfo* const user_model,
                                   base::OnceClosure barrier_closure,
                                   const SegmentList& segments) {
  CHECK(user_model);

  user_model->interest.segments = segments;
  std::move(barrier_closure).Run();
}

}  // namespace

void BuildUserModel(BuildUserModelCallback callback) {
  auto user_model = std::make_unique<UserModelInfo>();

  UserModelInfo* const user_model_ptr = user_model.get();

  auto barrier_closure = base::BarrierClosure(
      /*num_closures=*/3,
      base::BindOnce(
          [](std::unique_ptr<UserModelInfo> user_model,
             base::OnceCallback<void(UserModelInfo)> callback) {
            std::move(callback).Run(std::move(*user_model));
          },
          std::move(user_model), std::move(callback)));

  BuildIntentSegments(base::BindOnce(&BuildIntentSegmentsCallback,
                                     user_model_ptr, barrier_closure));

  BuildLatentInterestSegments(base::BindOnce(
      &BuildLatentInterestSegmentsCallback, user_model_ptr, barrier_closure));

  BuildInterestSegments(base::BindOnce(&BuildInterestSegmentsCallback,
                                       user_model_ptr, barrier_closure));
}

}  // namespace catsxp_ads
