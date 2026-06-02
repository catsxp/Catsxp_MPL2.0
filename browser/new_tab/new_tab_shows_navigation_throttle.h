/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_NAVIGATION_THROTTLE_H_
#define CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_NAVIGATION_THROTTLE_H_

#include "base/memory/weak_ptr.h"
#include "content/public/browser/navigation_throttle.h"
#include "url/gurl.h"

class NewTabShowsNavigationThrottle : public content::NavigationThrottle {
 public:
  explicit NewTabShowsNavigationThrottle(
      content::NavigationThrottleRegistry& registry);
  ~NewTabShowsNavigationThrottle() override;

  NewTabShowsNavigationThrottle(const NewTabShowsNavigationThrottle&) = delete;
  NewTabShowsNavigationThrottle& operator=(
      const NewTabShowsNavigationThrottle&) = delete;

  static void MaybeCreateAndAdd(content::NavigationThrottleRegistry& registry);

 private:
  // content::NavigationThrottle overrides:
  ThrottleCheckResult WillStartRequest() override;
  const char* GetNameForLogging() override;

  void LoadNewTabOptionsURL();

  GURL new_tab_options_url_;
  base::WeakPtrFactory<NewTabShowsNavigationThrottle> weak_factory_{this};
};

#endif  // CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_NAVIGATION_THROTTLE_H_
