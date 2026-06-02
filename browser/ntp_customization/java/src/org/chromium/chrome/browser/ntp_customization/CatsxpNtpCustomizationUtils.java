/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.ntp_customization;

import org.chromium.build.annotations.NullMarked;
import org.chromium.components.browser_ui.widget.displaystyle.UiConfig;

/**
 * Catsxp-specific NTP customization utilities. Used via bytecode to replace
 * NtpCustomizationUtils.isInNarrowWindowOnTablet to avoid leftMargin override to 0 at
 * NewTabPageLayout.updateMvtOnTablet on tablets and misalign of MVT area.
 */
@NullMarked
public class CatsxpNtpCustomizationUtils {
    private static final String TAG = "CatsxpNtpCustomizationUtils";

    /**
     * Replace NtpCustomizationUtils.isInNarrowWindowOnTablet. Catsxp returns true for any tablet to
     * avoid MVT layout misalignment.
     */
    public static boolean isInNarrowWindowOnTablet(boolean isTablet, UiConfig uiConfig) {
        return isTablet;
    }
}
