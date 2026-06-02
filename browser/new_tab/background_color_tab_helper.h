/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NEW_TAB_BACKGROUND_COLOR_TAB_HELPER_H_
#define CATSXP_BROWSER_NEW_TAB_BACKGROUND_COLOR_TAB_HELPER_H_

#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

// Sets root RenderWidgetHostView background color to the ntp background color
// to avoid white flash on a new tab (Windows-specific).
class BackgroundColorTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<BackgroundColorTabHelper> {
 public:
  explicit BackgroundColorTabHelper(content::WebContents* web_contents);
  ~BackgroundColorTabHelper() override;

  BackgroundColorTabHelper(const BackgroundColorTabHelper&) = delete;
  BackgroundColorTabHelper& operator=(const BackgroundColorTabHelper&) = delete;

 private:
  friend class content::WebContentsUserData<BackgroundColorTabHelper>;

  void RenderFrameCreated(content::RenderFrameHost* render_frame_host) override;

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

#endif  // CATSXP_BROWSER_NEW_TAB_BACKGROUND_COLOR_TAB_HELPER_H_
