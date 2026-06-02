/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.tab_group_sync;

import org.chromium.build.annotations.NullMarked;

@NullMarked
public class CatsxpStartupHelper {

    // Replace StartupHelper.handleUnsavedLocalTabGroups with empty implementation.
    // The reason for this - otherwise groups created with `Open tabs in current group` option
    // are wiped after app restart.
    public void handleUnsavedLocalTabGroups() {}
}
