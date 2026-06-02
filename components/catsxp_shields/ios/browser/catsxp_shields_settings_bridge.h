/* Copyright (c) 2023 The Catsxp Authors. All rights reserved. */

#ifndef CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_H_
#define CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_H_

#ifdef __cplusplus
#include "catsxp/components/catsxp_shields/ios/common/shields_settings.mojom.objc.h"
#else
#import "shields_settings.mojom.objc.h"
#endif

NS_SWIFT_NAME(CatsxpShieldsSettings)
@protocol CatsxpShieldsSettingsBridge

- (BOOL)catsxpShieldsEnabledFor:(NSURL*)url
    NS_SWIFT_NAME(isCatsxpShieldsEnabled(for:));
- (void)setCatsxpShieldsEnabled:(BOOL)isEnabled forURL:(NSURL*)url;

@property(nonatomic) CatsxpShieldsAdBlockMode defaultAdBlockMode;
- (CatsxpShieldsAdBlockMode)adBlockModeForURL:(NSURL*)url
    NS_SWIFT_NAME(adBlockMode(for:));
- (void)setAdBlockMode:(CatsxpShieldsAdBlockMode)adBlockMode forURL:(NSURL*)url;

@property(nonatomic, getter=isBlockScriptsEnabledByDefault)
    BOOL blockScriptsEnabledByDefault;
- (BOOL)blockScriptsEnabledForURL:(NSURL*)url
    NS_SWIFT_NAME(isBlockScriptsEnabled(for:));
- (void)setBlockScriptsEnabled:(BOOL)isEnabled forURL:(NSURL*)url;

@property(nonatomic) CatsxpShieldsFingerprintMode defaultFingerprintMode;
- (CatsxpShieldsFingerprintMode)fingerprintModeForURL:(NSURL*)url
    NS_SWIFT_NAME(fingerprintMode(for:));
- (void)setFingerprintMode:(CatsxpShieldsFingerprintMode)fingerprintMode
                    forURL:(NSURL*)url;

@property(nonatomic) CatsxpShieldsAutoShredMode defaultAutoShredMode;
- (CatsxpShieldsAutoShredMode)autoShredModeForURL:(NSURL*)url
    NS_SWIFT_NAME(autoShredMode(for:));
- (void)setAutoShredMode:(CatsxpShieldsAutoShredMode)autoShredMode
                  forURL:(NSURL*)url;

- (BOOL)isShieldsDisabledOnAnyHostMatchingDomainOf:(NSURL*)url
    NS_SWIFT_NAME(isShieldsDisabledOnAnyHostMatchingDomain(of:));

@end

#endif  // CATSXP_COMPONENTS_CATSXP_SHIELDS_IOS_BROWSER_CATSXP_SHIELDS_SETTINGS_BRIDGE_H_
