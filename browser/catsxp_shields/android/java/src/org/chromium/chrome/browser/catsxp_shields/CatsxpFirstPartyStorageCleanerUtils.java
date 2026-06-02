/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.catsxp_shields;

import org.jni_zero.JNINamespace;
import org.jni_zero.NativeMethods;

import org.chromium.build.annotations.NullMarked;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.tab.Tab;

@JNINamespace("catsxp_shields")
@NullMarked
public class CatsxpFirstPartyStorageCleanerUtils {
    private static final String TAG = "FPSCleanerUtils";

    public static void cleanupTLDFirstPartyStorage(Tab tab) {
        CatsxpFirstPartyStorageCleanerUtilsJni.get().cleanupTLDFirstPartyStorage(tab);
    }

    public static void triggerCurrentAppStateNotification(Profile profile) {
        CatsxpFirstPartyStorageCleanerUtilsJni.get().triggerCurrentAppStateNotification(profile);
    }

    @NativeMethods
    interface Natives {
        void cleanupTLDFirstPartyStorage(Tab tab);

        void triggerCurrentAppStateNotification(Profile profile);
    }
}
