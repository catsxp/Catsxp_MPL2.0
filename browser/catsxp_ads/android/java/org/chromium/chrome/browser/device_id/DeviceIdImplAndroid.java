/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.device_id;

import android.annotation.SuppressLint;
import android.content.Context;
import android.provider.Settings;

import org.jni_zero.CalledByNative;
import org.jni_zero.JNINamespace;

import org.chromium.base.ContextUtils;

@JNINamespace("catsxp_ads")
public class DeviceIdImplAndroid {
    @SuppressLint("HardwareIds")
    @CalledByNative
    public static String getAndroidId() {
        Context context = ContextUtils.getApplicationContext();
        return Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
    }
}
