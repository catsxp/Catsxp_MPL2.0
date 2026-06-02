/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

#include "catsxp/browser/catsxp_ads/application_state/application_state_monitor/application_state_monitor_mac.h"

#import <Cocoa/Cocoa.h>

#include "base/apple/foundation_util.h"
#include "base/apple/osstatus_logging.h"
#include "base/mac/mac_util.h"
#include "base/memory/raw_ptr.h"
#include "base/no_destructor.h"

@interface ApplicationStateMonitorDelegateMac : NSObject {
 @private
  raw_ptr<catsxp_ads::ApplicationStateMonitorMac> monitor_;  // Not owned.
}

- (instancetype)initWithMonitor:(catsxp_ads::ApplicationStateMonitorMac*)monitor;
- (void)appDidBecomeActive:(NSNotification*)notification;
- (void)appDidResignActive:(NSNotification*)notification;

@end

@implementation ApplicationStateMonitorDelegateMac

- (instancetype)initWithMonitor:
    (catsxp_ads::ApplicationStateMonitorMac*)monitor {
  if ((self = [super init])) {
    monitor_ = monitor;

    NSNotificationCenter* notification_center =
        [NSNotificationCenter defaultCenter];
    [notification_center addObserver:self
                            selector:@selector(appDidBecomeActive:)
                                name:NSApplicationDidBecomeActiveNotification
                              object:nil];
    [notification_center addObserver:self
                            selector:@selector(appDidResignActive:)
                                name:NSApplicationDidResignActiveNotification
                              object:nil];
  }
  return self;
}

- (void)appDidBecomeActive:(NSNotification*)notification {
  monitor_->OnBrowserDidBecomeActive();
}

- (void)appDidResignActive:(NSNotification*)notification {
  monitor_->OnBrowserDidResignActive();
}

@end

namespace catsxp_ads {

class ApplicationStateMonitorMac::Delegate {
 public:
  explicit Delegate(ApplicationStateMonitorMac* monitor) {
    delegate_ =
        [[ApplicationStateMonitorDelegateMac alloc] initWithMonitor:monitor];
  }

  ~Delegate() = default;

 private:
  ApplicationStateMonitorDelegateMac* __strong delegate_;
};

// static
ApplicationStateMonitor* ApplicationStateMonitor::GetInstance() {
  static base::NoDestructor<ApplicationStateMonitorMac> instance;
  return instance.get();
}

ApplicationStateMonitorMac::ApplicationStateMonitorMac() {
  delegate_ = std::make_unique<Delegate>(this);
}

ApplicationStateMonitorMac::~ApplicationStateMonitorMac() = default;

void ApplicationStateMonitorMac::OnBrowserDidBecomeActive() {
  NotifyBrowserDidBecomeActive();
}

void ApplicationStateMonitorMac::OnBrowserDidResignActive() {
  NotifyBrowserDidResignActive();
}

bool ApplicationStateMonitorMac::IsBrowserActive() const {
  return [[NSApplication sharedApplication] isActive];
}

}  // namespace catsxp_ads
