/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_IMPL_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_IMPL_H_

#import <Foundation/Foundation.h>

#include "base/memory/raw_ptr.h"
#include "catsxp/components/catsxp_shields/ios/browser/catsxp_shields_settings_bridge.h"
#include "catsxp/components/catsxp_shields/ios/common/shields_settings.mojom.objc.h"

NS_ASSUME_NONNULL_BEGIN

namespace catsxp_shields {
class CatsxpShieldsSettingsService;
}

@interface CatsxpShieldsSettingsBridgeImpl
    : NSObject <CatsxpShieldsSettingsBridge>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCatsxpShieldsSettings:
    (raw_ptr<catsxp_shields::CatsxpShieldsSettingsService>)catsxpShieldsSettings;

@end

NS_ASSUME_NONNULL_END

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_IMPL_H_
