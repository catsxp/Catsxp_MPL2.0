/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_BROWSER_SYNC_CATSXP_SYNC_DEVICES_ANDROID_H_
#define CATSXP_BROWSER_SYNC_CATSXP_SYNC_DEVICES_ANDROID_H_

#include <jni.h>

#include "base/android/jni_weak_ref.h"
#include "base/memory/raw_ptr.h"
#include "base/scoped_observation.h"
#include "base/values.h"
#include "components/sync_device_info/device_info_tracker.h"

class Profile;

namespace syncer {
class CatsxpSyncServiceImpl;
}

namespace chrome {
namespace android {

class CatsxpSyncDevicesAndroid : public syncer::DeviceInfoTracker::Observer {
 public:
  CatsxpSyncDevicesAndroid(JNIEnv* env,
                          const base::android::JavaRef<jobject>& obj);
  ~CatsxpSyncDevicesAndroid() override;

  void Destroy(JNIEnv* env);

  base::android::ScopedJavaLocalRef<jstring> GetSyncDeviceListJson(JNIEnv* env);

  void DeleteDevice(JNIEnv* env,
                    const base::android::JavaRef<jstring>& device_guid);

 private:
  // syncer::DeviceInfoTracker::Observer
  void OnDeviceInfoChange() override;

  base::ListValue GetSyncDeviceList();

  syncer::CatsxpSyncServiceImpl* GetSyncService() const;

  base::ScopedObservation<syncer::DeviceInfoTracker,
                          syncer::DeviceInfoTracker::Observer>
      device_info_tracker_observer_{this};

  JavaObjectWeakGlobalRef weak_java_catsxp_sync_worker_;
  raw_ptr<Profile> profile_ = nullptr;
};

}  // namespace android
}  // namespace chrome

#endif  // CATSXP_BROWSER_SYNC_CATSXP_SYNC_DEVICES_ANDROID_H_
