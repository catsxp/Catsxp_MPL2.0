/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_TYPES_H_
#define CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_TYPES_H_

#include <cstdint>

namespace catsxp_ads {

// WARNING: don't change these numbers. They are provided by the variations
// service, so will need the same values to match the enums

enum class UserActivityEventType : uint8_t {
  /*00*/ kInitializedAds = 0,
  /*01*/ kBrowserDidEnterForeground,
  /*02*/ kBrowserDidEnterBackground,
  /*03*/ kClickedBackOrForwardNavigationButtons,
  /*04*/ kClickedBookmark,
  /*05*/ kClickedHomePageButton,
  /*06*/ kClickedLink,
  /*07*/ kClickedReloadButton,
  /*08*/ kClosedTab,
  /*09*/ kTabChangedFocus,
  /*0A*/ kGeneratedKeyword,
  /*0B*/ kNewNavigation,
  /*0C*/ kOpenedLinkFromExternalApplication,
  /*0D*/ kOpenedNewTab,
  /*0E*/ kTabStartedPlayingMedia,
  /*0F*/ kTabStoppedPlayingMedia,
  /*10*/ kSubmittedForm,
  /*11*/ kTabDidChange,
  /*12*/ kTypedAndSelectedNonUrl,
  /*13*/ kTypedKeywordOtherThanDefaultSearchProvider,
  /*14*/ kTypedUrl,
  /*15*/ kUsedAddressBar,
  /*16*/ kBrowserDidBecomeActive,
  /*17*/ kBrowserDidResignActive
};

}  // namespace catsxp_ads

#endif  // CATSXP_COMPONENTS_CATSXP_ADS_CORE_INTERNAL_USER_ATTENTION_USER_ACTIVITY_USER_ACTIVITY_EVENT_TYPES_H_
