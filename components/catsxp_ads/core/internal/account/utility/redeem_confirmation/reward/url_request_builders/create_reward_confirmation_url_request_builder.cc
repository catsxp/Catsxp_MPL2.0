/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder.h"

#include <utility>
#include <vector>

#include "base/check.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/confirmations_util.h"
#include "catsxp/components/catsxp_ads/core/internal/account/confirmations/payload/confirmation_payload_json_writer.h"
#include "catsxp/components/catsxp_ads/core/internal/account/utility/redeem_confirmation/reward/url_request_builders/create_reward_confirmation_url_request_builder_util.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_types.h"
#include "catsxp/components/catsxp_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom.h"
#include "url/gurl.h"

namespace catsxp_ads {

namespace {

std::vector<std::string> BuildHeaders() {
  return {"accept: application/json"};
}

}  // namespace

CreateRewardConfirmationUrlRequestBuilder::
    CreateRewardConfirmationUrlRequestBuilder(ConfirmationInfo confirmation)
    : confirmation_(std::move(confirmation)) {
  CHECK(IsValid(confirmation_));
}

mojom::UrlRequestInfoPtr CreateRewardConfirmationUrlRequestBuilder::Build() {
  mojom::UrlRequestInfoPtr mojom_url_request = mojom::UrlRequestInfo::New();
  mojom_url_request->url = BuildUrl();
  mojom_url_request->headers = BuildHeaders();
  mojom_url_request->content = BuildBody();
  mojom_url_request->content_type = "application/json";
  mojom_url_request->method = mojom::UrlRequestMethodType::kPost;

  return mojom_url_request;
}

///////////////////////////////////////////////////////////////////////////////

GURL CreateRewardConfirmationUrlRequestBuilder::BuildUrl() const {
  CHECK(confirmation_.reward);

  const std::string url_host =
      confirmation_.ad_type == mojom::AdType::kSearchResultAd
          ? GetUrlHost(UrlHostType::kAnonymousSearch)
          : GetUrlHost(UrlHostType::kAnonymous);

  const std::string spec =
      url_host + BuildCreateRewardConfirmationUrlPath(
                     confirmation_.transaction_id,
                     confirmation_.reward->credential_base64url);

  return GURL(spec);
}

std::string CreateRewardConfirmationUrlRequestBuilder::BuildBody() const {
  return json::writer::WriteConfirmationPayload(confirmation_);
}

}  // namespace catsxp_ads
