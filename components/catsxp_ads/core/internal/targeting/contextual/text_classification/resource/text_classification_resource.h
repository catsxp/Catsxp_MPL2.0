/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_RESOURCE_TEXT_CLASSIFICATION_RESOURCE_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_RESOURCE_TEXT_CLASSIFICATION_RESOURCE_H_

#include <optional>
#include <string>

#include "base/functional/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/threading/sequence_bound.h"
#include "base/types/expected.h"
#include "base/types/optional_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/pipeline/text_processing/text_processing.h"
#include "catsxp/components/catsxp_ads/core/internal/ml/transformation/ml_types.h"
#include "catsxp/components/catsxp_ads/core/public/ads_client/ads_client_notifier_observer.h"

namespace catsxp_ads {

class AdsClient;

using ClassifyPageCallback =
    base::OnceCallback<void(base::optional_ref<const ml::PredictionMap>)>;

class TextClassificationResource final : public AdsClientNotifierObserver {
 public:
  TextClassificationResource();

  TextClassificationResource(const TextClassificationResource&) = delete;
  TextClassificationResource& operator=(const TextClassificationResource&) =
      delete;

  ~TextClassificationResource() override;

  bool IsLoaded() const { return !!text_processing_pipeline_; }

  std::optional<std::string> GetManifestVersion() const {
    return manifest_version_;
  }

  void ClassifyPage(const std::string& text, ClassifyPageCallback callback);

 private:
  void MaybeLoad();
  void MaybeLoadOrUnload();

  void Load();
  void LoadResourceComponentCallback(base::File file);
  void LoadCallback(base::expected<bool, std::string> result);

  void MaybeUnload();
  void Unload();

  // AdsClientNotifierObserver:
  void OnNotifyPrefDidChange(const std::string& path) override;
  void OnNotifyResourceComponentDidChange(const std::string& manifest_version,
                                          const std::string& id) override;
  void OnNotifyDidUnregisterResourceComponent(const std::string& id) override;

  std::optional<std::string> manifest_version_;

  std::optional<base::SequenceBound<ml::pipeline::TextProcessing>>
      text_processing_pipeline_;

  base::ScopedObservation<AdsClient, AdsClientNotifierObserver>
      ads_client_observation_{this};

  base::WeakPtrFactory<TextClassificationResource> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_RESOURCE_TEXT_CLASSIFICATION_RESOURCE_H_
