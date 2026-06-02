/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/components/catsxp_ads/core/internal/user_attention/user_activity/page_transition_util.h"

#include "ui/base/page_transition_types.h"

namespace catsxp_ads {

std::optional<UserActivityEventType> ToUserActivityEventType(
    ui::PageTransition page_transition) {
  switch (ui::PageTransitionStripQualifier(page_transition)) {
    case ui::PAGE_TRANSITION_LINK:
      return UserActivityEventType::kClickedLink;

    case ui::PAGE_TRANSITION_TYPED:
      return UserActivityEventType::kTypedUrl;

    case ui::PAGE_TRANSITION_AUTO_BOOKMARK:
      return UserActivityEventType::kClickedBookmark;

    case ui::PAGE_TRANSITION_GENERATED:
      return UserActivityEventType::kTypedAndSelectedNonUrl;

    case ui::PAGE_TRANSITION_FORM_SUBMIT:
      return UserActivityEventType::kSubmittedForm;

    case ui::PAGE_TRANSITION_RELOAD:
      return UserActivityEventType::kClickedReloadButton;

    case ui::PAGE_TRANSITION_KEYWORD:
      return UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider;

    case ui::PAGE_TRANSITION_KEYWORD_GENERATED:
      return UserActivityEventType::kGeneratedKeyword;

    default:
      return std::nullopt;
  }
}

}  // namespace catsxp_ads
