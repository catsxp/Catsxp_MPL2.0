/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/new_tab/background_color_tab_helper.h"

#include "chrome/browser/ui/color/chrome_color_id.h"
#include "content/public/browser/render_widget_host_view.h"
#include "ui/color/color_provider.h"

BackgroundColorTabHelper::BackgroundColorTabHelper(
    content::WebContents* web_contents)
    : WebContentsObserver(web_contents),
      content::WebContentsUserData<BackgroundColorTabHelper>(*web_contents) {}

BackgroundColorTabHelper::~BackgroundColorTabHelper() = default;

void BackgroundColorTabHelper::RenderFrameCreated(
    content::RenderFrameHost* render_frame_host) {
  if (render_frame_host->GetParent()) {
    return;
  }

  auto* view = render_frame_host->GetView();
  if (view) {
    view->SetBackgroundColor(web_contents()->GetColorProvider().GetColor(
        kColorNewTabPageBackground));
  }
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(BackgroundColorTabHelper);
