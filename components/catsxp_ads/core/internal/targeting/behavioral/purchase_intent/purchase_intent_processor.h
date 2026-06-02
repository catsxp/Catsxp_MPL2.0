/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_

#include <cstdint>
#include <map>
#include <optional>
#include <string>

#include "base/memory/raw_ref.h"
#include "base/scoped_observation.h"
#include "catsxp/components/catsxp_ads/core/internal/segments/segment_types.h"
#include "catsxp/components/catsxp_ads/core/internal/tabs/tab_manager_observer.h"
#include "catsxp/components/catsxp_ads/core/internal/targeting/behavioral/purchase_intent/keyphrase/purchase_intent_keyphrase_types.h"

class GURL;

namespace catsxp_ads {

class PurchaseIntentResource;
class TabManager;
struct PurchaseIntentFunnelInfo;
struct PurchaseIntentSignalInfo;
struct TabInfo;

class PurchaseIntentProcessor final : public TabManagerObserver {
 public:
  explicit PurchaseIntentProcessor(PurchaseIntentResource& resource);

  PurchaseIntentProcessor(const PurchaseIntentProcessor&) = delete;
  PurchaseIntentProcessor& operator=(const PurchaseIntentProcessor&) = delete;

  ~PurchaseIntentProcessor() override;

  void Process(const GURL& url);

 private:
  bool ShouldProcess(int32_t tab_id, const GURL& url) const;
  void MaybeProcess(int32_t tab_id, const GURL& url);

  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignal(
      const GURL& url) const;
  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignalForSearchQuery(
      const std::string& search_query) const;
  std::optional<SegmentList> MaybeGetSegmentsForSearchQuery(
      const KeywordList& search_query_keywords) const;
  int ComputeFunnelKeyphraseWeightForSearchQuery(
      const KeywordList& search_query_keywords) const;

  std::optional<PurchaseIntentSignalInfo> MaybeExtractSignalForUrl(
      const GURL& url) const;
  std::optional<PurchaseIntentFunnelInfo> MaybeGetFunnelForUrl(
      const GURL& url) const;

  // TabManagerObserver:
  void OnDidOpenNewTab(const TabInfo& tab) override;
  void OnTabDidChange(const TabInfo& tab) override;
  void OnDidCloseTab(int32_t tab_id) override;

  base::ScopedObservation<TabManager, TabManagerObserver>
      tab_manager_observation_{this};

  std::map</*tab_id*/ int32_t, GURL> tabs_;

  const raw_ref<PurchaseIntentResource> resource_;
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_PROCESSOR_H_
