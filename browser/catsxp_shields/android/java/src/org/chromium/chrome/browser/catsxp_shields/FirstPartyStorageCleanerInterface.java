/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.catsxp_shields;

import org.chromium.build.annotations.NullMarked;

@NullMarked
public interface FirstPartyStorageCleanerInterface {
    void shredSiteData();
}
