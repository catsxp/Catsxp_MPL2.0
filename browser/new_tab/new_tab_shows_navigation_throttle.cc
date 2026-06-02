/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/new_tab/new_tab_shows_navigation_throttle.h"

#include <string>

#include "base/functional/bind.h"
#include "base/task/sequenced_task_runner.h"
#include "catsxp/browser/new_tab/new_tab_shows_options.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/ntp/new_tab_ui.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/web_contents.h"

// static
void NewTabShowsNavigationThrottle::MaybeCreateAndAdd(
    content::NavigationThrottleRegistry& registry) {
  auto& navigation_handle = registry.GetNavigationHandle();
  auto* context = navigation_handle.GetWebContents()->GetBrowserContext();
  if (!Profile::FromBrowserContext(context)->IsRegularProfile() ||
      !NewTabUI::IsNewTab(navigation_handle.GetURL())) {
    return;
  }

  registry.AddThrottle(
      std::make_unique<NewTabShowsNavigationThrottle>(registry));
}

NewTabShowsNavigationThrottle::NewTabShowsNavigationThrottle(
    content::NavigationThrottleRegistry& registry)
    : NavigationThrottle(registry) {}
NewTabShowsNavigationThrottle::~NewTabShowsNavigationThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult
NewTabShowsNavigationThrottle::WillStartRequest() {
  auto* web_contents = navigation_handle()->GetWebContents();
  auto* context = web_contents->GetBrowserContext();
  Profile* profile = Profile::FromBrowserContext(context);
  if (catsxp::ShouldUseNewTabURLForNewTab(profile)) {
    return content::NavigationThrottle::PROCEED;
  }

  new_tab_options_url_ = catsxp::GetNewTabPageURL(profile);
  base::SequencedTaskRunner::GetCurrentDefault()->PostTask(
      FROM_HERE,
      base::BindOnce(&NewTabShowsNavigationThrottle::LoadNewTabOptionsURL,
                     weak_factory_.GetWeakPtr()));
  return content::NavigationThrottle::CANCEL;
}

const char* NewTabShowsNavigationThrottle::GetNameForLogging() {
  return "NewTabShowsNavigationThrottle";
}

void NewTabShowsNavigationThrottle::LoadNewTabOptionsURL() {
  auto* web_contents = navigation_handle()->GetWebContents();
  web_contents->GetController().LoadURL(
      new_tab_options_url_, content::Referrer(),
      ui::PAGE_TRANSITION_AUTO_TOPLEVEL, std::string());
}
