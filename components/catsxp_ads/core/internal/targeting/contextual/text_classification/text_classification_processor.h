/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_

#include <cstdint>
#include <string>

#include "base/containers/span.h"
#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/types/optional_ref.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/contextual/text_classification/text_classification_types.h"
#include "url/gurl.h"

namespace catsxp_ads {

class TabManager;
class TextClassificationResource;

class TextClassificationProcessor final : public TabManagerObserver {
 public:
  explicit TextClassificationProcessor(TextClassificationResource& resource);

  TextClassificationProcessor(const TextClassificationProcessor&) = delete;
  TextClassificationProcessor& operator=(const TextClassificationProcessor&) =
      delete;

  ~TextClassificationProcessor() override;

  void Process(const std::string& text);

 private:
  void ClassifyPageCallback(
      uint64_t trace_id,
      base::optional_ref<const TextClassificationProbabilityMap> probabilities);

  // TabManagerObserver:
  void OnTextContentDidChange(int32_t tab_id,
                              base::span<const GURL> redirect_chain,
                              const std::string& text) override;

  base::ScopedObservation<TabManager, TabManagerObserver>
      tab_manager_observation_{this};

  const raw_ref<TextClassificationResource> resource_;

  base::WeakPtrFactory<TextClassificationProcessor> weak_factory_{this};
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_CONTEXTUAL_TEXT_CLASSIFICATION_TEXT_CLASSIFICATION_PROCESSOR_H_
