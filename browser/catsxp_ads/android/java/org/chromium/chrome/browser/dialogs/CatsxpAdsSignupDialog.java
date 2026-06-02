/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

package org.chromium.chrome.browser.dialogs;

import android.app.AlarmManager;
import android.app.AlertDialog;
import android.app.PendingIntent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.view.View;
import android.widget.ImageView;

import org.jni_zero.CalledByNative;

import org.chromium.base.ContextUtils;
import org.chromium.base.IntentUtils;
import org.chromium.base.Log;
import org.chromium.base.shared_preferences.SharedPreferencesManager;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.CatsxpRewardsNativeWorker;
import org.chromium.chrome.browser.app.CatsxpActivity;
import org.chromium.chrome.browser.notifications.CatsxpOnboardingNotification;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.preferences.ChromeSharedPreferences;
import org.chromium.chrome.browser.settings.AppearancePreferences;
import org.chromium.chrome.browser.util.PackageUtils;

public class CatsxpAdsSignupDialog {
    private static final String TAG = "CatsxpAdsSignupDialog";

    private static final String SHOULD_SHOW_ONBOARDING_DIALOG_VIEW_COUNTER =
            "should_show_onboarding_dialog_view_counter";
    private static final String SHOULD_SHOW_ONBOARDING_DIALOG = "should_show_onboarding_dialog";

    private static final long TWENTY_FOUR_HOURS = 86_400_000;
    private static final long MOMENT_LATER = 2_500;

    public static boolean shouldShowNewUserDialog(Context context) {
        CatsxpRewardsNativeWorker catsxpRewardsNativeWorker = CatsxpRewardsNativeWorker.getInstance();
        boolean shouldShow =
                shouldShowOnboardingDialog()
                        && PackageUtils.isFirstInstall(context)
                        && hasElapsed24Hours(context)
                        && catsxpRewardsNativeWorker != null
                        && !catsxpRewardsNativeWorker.isRewardsEnabled()
                        && catsxpRewardsNativeWorker.isSupported();

        boolean shouldShowForViewCount = shouldShowForViewCount();
        if (shouldShow) updateViewCount();

        return shouldShow && shouldShowForViewCount;
    }

    public static boolean shouldShowNewUserDialogIfRewardsIsSwitchedOff(Context context) {
        CatsxpRewardsNativeWorker catsxpRewardsNativeWorker = CatsxpRewardsNativeWorker.getInstance();
        boolean shouldShow =
                shouldShowOnboardingDialog()
                        && !PackageUtils.isFirstInstall(context)
                        && catsxpRewardsNativeWorker != null
                        && !catsxpRewardsNativeWorker.isRewardsEnabled()
                        && catsxpRewardsNativeWorker.isSupported();

        boolean shouldShowForViewCount = shouldShowForViewCount();
        if (shouldShow) updateViewCount();

        return shouldShow && shouldShowForViewCount;
    }

    public static boolean shouldShowExistingUserDialog(Context context) {
        CatsxpRewardsNativeWorker catsxpRewardsNativeWorker = CatsxpRewardsNativeWorker.getInstance();
        boolean shouldShow =
                shouldShowOnboardingDialog()
                        && !PackageUtils.isFirstInstall(context)
                        && catsxpRewardsNativeWorker != null
                        && !catsxpRewardsNativeWorker.isRewardsEnabled()
                        && catsxpRewardsNativeWorker.isSupported();

        boolean shouldShowForViewCount = shouldShowForViewCount();
        if (shouldShow) updateViewCount();

        return shouldShow && shouldShowForViewCount;
    }

    @CalledByNative
    public static void enqueueOnboardingNotificationNative() {
        enqueueOnboardingNotification(ContextUtils.getApplicationContext());
    }

    @CalledByNative
    public static boolean showAdsInBackground() {
        return AppearancePreferences.getPrefAdsInBackgroundEnabled();
    }

    private static void enqueueOnboardingNotification(Context context) {
        if (!OnboardingPrefManager.getInstance().isOnboardingNotificationShown()) {
            AlarmManager am = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
            Intent intent = new Intent(context, CatsxpOnboardingNotification.class);
            am.set(
                    AlarmManager.RTC_WAKEUP,
                    System.currentTimeMillis() + MOMENT_LATER,
                    PendingIntent.getBroadcast(
                            context,
                            0,
                            intent,
                            PendingIntent.FLAG_UPDATE_CURRENT
                                    | IntentUtils.getPendingIntentMutabilityFlag(true)));
        }
    }

    public static void showNewUserDialog(Context context) {
        AlertDialog alertDialog = new AlertDialog.Builder(context, R.style.CatsxpDialogTheme)
        .setView(R.layout.catsxp_ads_new_user_dialog_layout)
        .setPositiveButton(R.string.catsxp_ads_offer_positive, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

                OnboardingPrefManager.getInstance().setOnboardingNotificationShown(false);

                neverShowOnboardingDialogAgain();
                try {
                    // Enable ads
                    CatsxpActivity.getCatsxpActivity().openRewardsPanel();
                } catch (CatsxpActivity.CatsxpActivityNotFoundException e) {
                    Log.e(TAG, "showNewUserDialog " + e);
                }
            }
        }).create();
        alertDialog.show();

        ImageView closeButton = alertDialog.findViewById(R.id.close_button);
        closeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                alertDialog.cancel();
            }
        });
    }

    public static void showExistingUserDialog(Context context) {
        AlertDialog alertDialog = new AlertDialog.Builder(context, R.style.CatsxpDialogTheme)
        .setView(R.layout.catsxp_ads_existing_user_dialog_layout)
        .setPositiveButton(R.string.catsxp_ads_offer_positive, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                // Enable ads
                neverShowOnboardingDialogAgain();
                try {
                    CatsxpActivity catsxpActivity = CatsxpActivity.getCatsxpActivity();
                    catsxpActivity.openRewardsPanel();
                } catch (CatsxpActivity.CatsxpActivityNotFoundException e) {
                    Log.e(TAG, "showExistingUserDialog " + e);
                }
            }
        }).create();
        alertDialog.show();

        ImageView closeButton = alertDialog.findViewById(R.id.close_button);
        closeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                alertDialog.cancel();
            }
        });
    }

    private static boolean hasElapsed24Hours(Context context) {
        boolean result = false;
        try {
            result = System.currentTimeMillis() >= context.getPackageManager().getPackageInfo(context.getPackageName(), 0).firstInstallTime + TWENTY_FOUR_HOURS;
        } catch (NameNotFoundException e) {}
        return result;
    }

    private static boolean shouldShowForViewCount() {
        int viewCount =
                ChromeSharedPreferences.getInstance()
                        .readInt(SHOULD_SHOW_ONBOARDING_DIALOG_VIEW_COUNTER, 0);

        return 0 == viewCount || 20 == viewCount || 40 == viewCount;
    }

    private static void updateViewCount() {
        SharedPreferencesManager sharedPreferencesManager = ChromeSharedPreferences.getInstance();
        sharedPreferencesManager.writeInt(
                SHOULD_SHOW_ONBOARDING_DIALOG_VIEW_COUNTER,
                sharedPreferencesManager.readInt(SHOULD_SHOW_ONBOARDING_DIALOG_VIEW_COUNTER, 0)
                        + 1);
    }

    private static void neverShowOnboardingDialogAgain() {
        ChromeSharedPreferences.getInstance().writeBoolean(SHOULD_SHOW_ONBOARDING_DIALOG, false);
    }

    private static boolean shouldShowOnboardingDialog() {
        return ChromeSharedPreferences.getInstance()
                .readBoolean(SHOULD_SHOW_ONBOARDING_DIALOG, true);
    }
}
