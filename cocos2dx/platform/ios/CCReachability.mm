/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "CCReachability.h"
#import "Reachability.h"
#include "CCNotificationCenter.h"
#include "cocoa/CCInteger.h"

@interface ReachabilityAgent : NSObject

@property (nonatomic, strong) Reachability* r;

- (void)startMonitorHost:(NSString*)host;
- (void)onReachabilityChanged:(NSNotification*)n;

@end

@implementation ReachabilityAgent

- (instancetype)init {
    if(self = [super init]) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onReachabilityChanged:)
                                                     name:kReachabilityChangedNotification
                                                   object:nil];
    }
    return self;
}

- (void)dealloc {
    [super dealloc];
    
    // remove observer
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kReachabilityChangedNotification
                                                  object:nil];
    
    // release reachability
    if(self.r) {
        [self.r release];
        self.r = nil;
    }
}

- (void)startMonitorHost:(NSString *)host {
    // release old
    if(self.r) {
        [self.r stopNotifier];
        [self.r release];
        self.r = nil;
    }
    
    // create reachability
    self.r = [Reachability reachabilityWithHostName:host];
    [self.r startNotifier];
}

- (void)onReachabilityChanged:(NSNotification*)n {
    Reachability* curReach = [n object];
    NetworkStatus netStatus = [curReach currentReachabilityStatus];
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(kCCNotificationReachabilityChanged,
                                                                                cocos2d::CCInteger::create(netStatus));
}

@end

NS_CC_BEGIN

static ReachabilityAgent* s_agent = nil;

void CCReachability::startMonitorHost(const string& host) {
    if(!s_agent) {
        s_agent = [[ReachabilityAgent alloc] init];
    }
    [s_agent startMonitorHost:[NSString stringWithCString:host.c_str() encoding:NSUTF8StringEncoding]];
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
