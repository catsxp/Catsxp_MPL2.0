/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.chrome.browser.profiles.Profile;

@JNINamespace("catsxp_ads")
public class CatsxpAdsNativeHelper {
    private CatsxpAdsNativeHelper() {}

    public static boolean nativeIsOptedInToNotificationAds(Profile profile) {
        return CatsxpAdsNativeHelperJni.get().isOptedInToNotificationAds(profile);
    }

    public static void nativeSetOptedInToNotificationAds(Profile profile, boolean optedIn) {
        CatsxpAdsNativeHelperJni.get().setOptedInToNotificationAds(profile, optedIn);
    }

    public static boolean nativeIsSupportedRegion(Profile profile) {
        return CatsxpAdsNativeHelperJni.get().isSupportedRegion(profile);
    }

    public static void nativeClearData(Profile profile) {
        CatsxpAdsNativeHelperJni.get().clearData(profile);
    }

    public static void nativeOnNotificationAdShown(Profile profile, String jNotificationId) {
        CatsxpAdsNativeHelperJni.get().onNotificationAdShown(profile, jNotificationId);
    }

    public static void nativeOnNotificationAdClosed(
            Profile profile, String jNotificationId, boolean jByUser) {
        CatsxpAdsNativeHelperJni.get().onNotificationAdClosed(profile, jNotificationId, jByUser);
    }

    public static void nativeOnNotificationAdClicked(Profile profile, String jNotificationId) {
        CatsxpAdsNativeHelperJni.get().onNotificationAdClicked(profile, jNotificationId);
    }

    @NativeMethods
    interface Natives {
        boolean isOptedInToNotificationAds(Profile profile);

        void setOptedInToNotificationAds(Profile profile, boolean optedIn);

        boolean isSupportedRegion(Profile profile);

        void clearData(Profile profile);

        void onNotificationAdShown(Profile profile, String jNotificationId);

        void onNotificationAdClosed(Profile profile, String jNotificationId, boolean jByUser);

        void onNotificationAdClicked(Profile profile, String jNotificationId);
    }
}
