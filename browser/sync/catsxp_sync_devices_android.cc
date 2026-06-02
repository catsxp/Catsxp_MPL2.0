/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/sync/catsxp_sync_devices_android.h"

#include <string>
#include <utility>

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/json/json_writer.h"
#include "base/logging.h"
#include "catsxp/components/catsxp_sync/sync_service_impl_helper.h"
#include "catsxp/components/sync/service/catsxp_sync_service_impl.h"
#include "chrome/android/chrome_jni_headers/CatsxpSyncDevices_jni.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/sync/device_info_sync_service_factory.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "components/sync_device_info/device_info_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"
#include "components/sync_device_info/local_device_info_provider.h"

namespace chrome {
namespace android {

CatsxpSyncDevicesAndroid::CatsxpSyncDevicesAndroid(
    JNIEnv* env, const base::android::JavaRef<jobject>& obj) :
    weak_java_catsxp_sync_worker_(env, obj) {
  Java_CatsxpSyncDevices_setNativePtr(env, obj,
    reinterpret_cast<intptr_t>(this));

  profile_ =
      ProfileManager::GetActiveUserProfile()->GetOriginalProfile();
  DCHECK_NE(profile_, nullptr);

  syncer::DeviceInfoTracker* tracker =
    DeviceInfoSyncServiceFactory::GetForProfile(profile_)
       ->GetDeviceInfoTracker();
  DCHECK(tracker);
  if (tracker) {
    device_info_tracker_observer_.Observe(tracker);
  }
}

CatsxpSyncDevicesAndroid::~CatsxpSyncDevicesAndroid() {
  // Observer will be removed by ScopedObservation
}

void CatsxpSyncDevicesAndroid::Destroy(JNIEnv* env) {
  delete this;
}

void CatsxpSyncDevicesAndroid::OnDeviceInfoChange() {
  // Notify Java code
  JNIEnv* env = base::android::AttachCurrentThread();
  Java_CatsxpSyncDevices_deviceInfoChanged(env,
      weak_java_catsxp_sync_worker_.get(env));
}

base::ListValue CatsxpSyncDevicesAndroid::GetSyncDeviceList() {
  auto* device_info_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  syncer::DeviceInfoTracker* tracker =
      device_info_service->GetDeviceInfoTracker();
  DCHECK(tracker);
  const syncer::DeviceInfo* local_device_info = device_info_service
     ->GetLocalDeviceInfoProvider()->GetLocalDeviceInfo();

  base::ListValue device_list;

  for (const auto& device : tracker->GetAllCatsxpDeviceInfo()) {
    auto device_value = device->ToValue();
    bool is_current_device =
        local_device_info && local_device_info->guid() == device->guid();
    device_value.Set("isCurrentDevice", is_current_device);
    // DeviceInfo::ToValue doesn't put guid
    device_value.Set("guid", device->guid());
    device_value.Set(
        "supportsSelfDelete",
        device->self_delete_support() == syncer::SelfDeleteSupport::kSupported);
    device_list.Append(std::move(device_value));
  }

  return device_list;
}

base::android::ScopedJavaLocalRef<jstring>
CatsxpSyncDevicesAndroid::GetSyncDeviceListJson(JNIEnv* env) {
  std::string json_string;
  if (!base::JSONWriter::Write(GetSyncDeviceList(), &json_string)) {
    VLOG(1) << "Writing as JSON failed. Passing empty string to Java code.";
    json_string = std::string();
  }

  return base::android::ConvertUTF8ToJavaString(env, json_string);
}

// TODO(AlexeyBarabash): duplicate with CatsxpSyncWorker?
syncer::CatsxpSyncServiceImpl* CatsxpSyncDevicesAndroid::GetSyncService() const {
  return SyncServiceFactory::IsSyncAllowed(profile_)
             ? static_cast<syncer::CatsxpSyncServiceImpl*>(
                   SyncServiceFactory::GetForProfile(profile_))
             : nullptr;
}

void CatsxpSyncDevicesAndroid::DeleteDevice(
    JNIEnv* env,
    const base::android::JavaRef<jstring>& device_guid) {
  std::string str_device_guid =
      base::android::ConvertJavaStringToUTF8(device_guid);
  auto* sync_service = GetSyncService();
  DCHECK(sync_service);

  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  DCHECK(device_info_sync_service);

  catsxp_sync::DeleteDevice(sync_service, device_info_sync_service,
                           str_device_guid);
}

static void JNI_CatsxpSyncDevices_Init(
    JNIEnv* env,
    const base::android::JavaRef<jobject>& jcaller) {
  new CatsxpSyncDevicesAndroid(env, jcaller);
}

}  // namespace android
}  // namespace chrome

DEFINE_JNI(CatsxpSyncDevices)
