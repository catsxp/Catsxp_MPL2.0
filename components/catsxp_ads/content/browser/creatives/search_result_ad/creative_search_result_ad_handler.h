/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_HANDLER_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_HANDLER_H_

#include <memory>
#include <vector>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "catsxp/components/catsxp_ads/core/mojom/catsxp_ads.mojom-forward.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "third_party/blink/public/mojom/document_metadata/document_metadata.mojom-forward.h"

class GURL;

namespace content {
class RenderFrameHost;
}  // namespace content

namespace catsxp_ads {

using ExtractCreativeAdPlacementIdsFromWebPageCallback =
    base::OnceCallback<void(std::vector<mojom::CreativeSearchResultAdInfoPtr>
                                creative_search_result_ads)>;

class AdsService;

class CreativeSearchResultAdHandler final {
 public:
  CreativeSearchResultAdHandler(const CreativeSearchResultAdHandler&) = delete;
  CreativeSearchResultAdHandler& operator=(
      const CreativeSearchResultAdHandler&) = delete;

  ~CreativeSearchResultAdHandler();

  static std::unique_ptr<CreativeSearchResultAdHandler> MaybeCreate(
      AdsService* ads_service,
      const GURL& url,
      bool should_trigger_creative_ad_viewed_events);

  void MaybeExtractCreativeAdPlacementIdsFromWebPage(
      content::RenderFrameHost* render_frame_host,
      ExtractCreativeAdPlacementIdsFromWebPageCallback callback);

  void MaybeTriggerCreativeAdViewedEvent(
      mojom::CreativeSearchResultAdInfoPtr creative_search_result_ad);

 private:
  friend class CatsxpAdsCreativeSearchResultAdHandlerTest;

  CreativeSearchResultAdHandler(AdsService& ads_service,
                                bool should_trigger_creative_ad_viewed_events);

  void MaybeExtractCreativeAdPlacementIdsFromWebPageCallback(
      mojo::Remote<blink::mojom::DocumentMetadata> document_metadata_remote,
      ExtractCreativeAdPlacementIdsFromWebPageCallback callback,
      blink::mojom::WebPagePtr mojom_web_page);

  const raw_ref<AdsService> ads_service_;

  const bool should_trigger_creative_ad_viewed_events_;

  base::WeakPtrFactory<CreativeSearchResultAdHandler> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CONTENT_BROWSER_CREATIVES_SEARCH_RESULT_AD_CREATIVE_SEARCH_RESULT_AD_HANDLER_H_
