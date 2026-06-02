/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_shields/catsxp_shields_web_contents_observer.h"

#include <string>

#include "catsxp/browser/android/catsxp_shields_content_settings.h"
#include "chrome/browser/android/tab_android.h"
#include "content/public/browser/web_contents.h"

using content::WebContents;

namespace catsxp_shields {
// static
void CatsxpShieldsWebContentsObserver::DispatchBlockedEventForWebContents(
    const std::string& block_type,
    const std::string& subresource,
    WebContents* web_contents) {
  if (!web_contents) {
    return;
  }

  int tabId = 0;
  TabAndroid* tab = TabAndroid::FromWebContents(web_contents);
  if (tab) {
    tabId = tab->GetAndroidId();
  }
  chrome::android::CatsxpShieldsContentSettings::DispatchBlockedEvent(
      tabId, block_type, subresource);
}

}  // namespace catsxp_shields
