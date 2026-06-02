/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.notifications;

import org.jni_zero.CalledByNative;

import org.chromium.chrome.browser.notifications.channels.CatsxpChannelDefinitions;

/**
 * This class provides the Catsxp Ads related methods for the native library
 * (catsxp/components/catsxp_ads/browser/notification_helper_android)
 */
public abstract class CatsxpAds {
    @CalledByNative
    public static String getCatsxpAdsChannelId() {
        return CatsxpChannelDefinitions.ChannelId.CATSXP_ADS;
    }

    @CalledByNative
    public static String getCatsxpAdsBackgroundChannelId() {
        return CatsxpChannelDefinitions.ChannelId.CATSXP_ADS_BACKGROUND;
    }
}
