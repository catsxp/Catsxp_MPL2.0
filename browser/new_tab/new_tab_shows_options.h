/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
#define CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_

#include "base/values.h"
#include "url/gurl.h"

class Profile;

namespace catsxp {

enum class NewTabPageShowsOptions {
  kDashboard,
  kHomepage,
  kBlankpage
};

GURL GetNewTabPageURL(Profile* profile);
base::ListValue GetNewTabShowsOptionsList(Profile* profile);
bool ShouldUseNewTabURLForNewTab(Profile* profile);
bool ShouldNewTabShowDashboard(Profile* profile);
bool ShouldNewTabShowBlankpage(Profile* profile);

}  // namespace catsxp

#endif  // CATSXP_BROWSER_NEW_TAB_NEW_TAB_SHOWS_OPTIONS_H_
