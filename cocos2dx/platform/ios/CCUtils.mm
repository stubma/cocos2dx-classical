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

#import "support/utils/CCUtils.h"
#import "sys/utsname.h"
#include <net/if.h>
#include <net/if_dl.h>
#import <StoreKit/StoreKit.h>
#import "EAGLView.h"
#include "CCLocale.h"
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AudioToolbox/AudioToolbox.h>

USING_NS_CC;

#pragma mark -
#pragma mark delegate of system dialog

@interface CCSystemConfirmDialogDelegate : NSObject <UIAlertViewDelegate> {
@private
	CCCallFunc* m_onOK;
	CCCallFunc* m_onCancel;
}

- (id)initWithOK:(CCCallFunc*)onOK cancel:(CCCallFunc*)onCancel;

@end

@implementation CCSystemConfirmDialogDelegate

- (id)initWithOK:(CCCallFunc*)onOK cancel:(CCCallFunc*)onCancel {
	if(self = [super init]) {
		m_onOK = onOK;
		m_onCancel = onCancel;
        CC_SAFE_RETAIN(m_onOK);
        CC_SAFE_RETAIN(m_onCancel);
		return self;
	}
	return nil;
}

- (void)dealloc {
    CC_SAFE_RELEASE(m_onOK);
    CC_SAFE_RELEASE(m_onCancel);
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
	if(buttonIndex == alertView.cancelButtonIndex) {
		if(m_onCancel)
			m_onCancel->execute();
	} else if(buttonIndex == alertView.firstOtherButtonIndex) {
		if(m_onOK)
			m_onOK->execute();
	}
	
    // release
#if !__has_feature(objc_arc)
	[self autorelease];
#endif
}

@end

#pragma mark -
#pragma mark delegate of app store view

@interface SKStoreProductViewControllerDelegate_openAppInStore : NSObject <SKStoreProductViewControllerDelegate>
@end

@implementation SKStoreProductViewControllerDelegate_openAppInStore

- (void)productViewControllerDidFinish:(SKStoreProductViewController *)viewController {
    [viewController dismissViewControllerAnimated:YES completion:^{
#if !__has_feature(objc_arc)
        [viewController autorelease];
		[self autorelease];
#endif
    }];
}

@end

#pragma mark -
#pragma mark CCUtils implementation on iOS

NS_CC_BEGIN

void CCUtils::openUrl(const string& url) {
    NSURL* nsUrl = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    [[UIApplication sharedApplication] openURL:nsUrl];
}

void CCUtils::openAppInStore(const string& appId) {
    // XXX: for now we still use web, later we will change
//	if([[UIDevice currentDevice].systemVersion floatValue] < 6.0f) {
		NSString* urlStr = [NSString stringWithFormat:@"itms-apps://itunes.apple.com/us/app/id%s?mt=8", appId.c_str()];
		NSURL* url = [NSURL URLWithString:urlStr];
		[[UIApplication sharedApplication] openURL:url];
//	} else {
//		SKStoreProductViewController* storeProductVC = [[SKStoreProductViewController alloc] init];
//		storeProductVC.delegate = [[SKStoreProductViewControllerDelegate_openAppInStore alloc] init];
//		NSDictionary* dict = [NSDictionary dictionaryWithObject:[NSString stringWithUTF8String:appId.c_str()]
//														 forKey:SKStoreProductParameterITunesItemIdentifier];
//		[storeProductVC loadProductWithParameters:dict completionBlock:^(BOOL result, NSError* error) {
//			if (result) {
//				UIViewController* vc = CCUtils::findViewController([EAGLView sharedEGLView]);
//				[vc presentViewController:storeProductVC animated:YES completion:nil];
//			}
//		}];
//	}
}

void CCUtils::showSystemConfirmDialog(const char* title, const char* msg, const char* positiveButton, const char* negativeButton, CCCallFunc* onOK, CCCallFunc* onCancel) {
	NSString* cancelButtonTitle = negativeButton ? [NSString stringWithUTF8String:negativeButton] : nil;
	NSString* okButtonTitle = positiveButton ? [NSString stringWithUTF8String:positiveButton] : nil;
    
	// create alert view
	UIAlertView* alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:msg]
												   delegate:[[CCSystemConfirmDialogDelegate alloc] initWithOK:onOK cancel:onCancel]
										  cancelButtonTitle:cancelButtonTitle
										  otherButtonTitles:okButtonTitle, nil];
	[alert performSelectorOnMainThread:@selector(show)
							withObject:nil
						 waitUntilDone:NO];
    
    // release
#if !__has_feature(objc_arc)
    [alert release];
#endif
}

int CCUtils::getCpuHz() {
    // get hardward string
    size_t size = 100;
    char* hw_machine = (char*)malloc(size);
    int name[] = {CTL_HW, HW_MACHINE};
    sysctl(name, 2, hw_machine, &size, NULL, 0);
    string hw = hw_machine;
    free(hw_machine);
    
    // check
    if(startsWith(hw, "iPhone")) {
        string majorMinor = hw.substr(6);
        CCArray& parts = componentsOfString(majorMinor, ',');
        int major = atoi(((CCString*)parts.objectAtIndex(0))->getCString());
        if(major < 4)
            return 500000000;
        else if(major == 4)
            return 800000000;
        else
            return 1500000000;
    } else if(startsWith(hw, "iPod")) {
        string majorMinor = hw.substr(4);
        CCArray& parts = componentsOfString(majorMinor, ',');
        int major = atoi(((CCString*)parts.objectAtIndex(0))->getCString());
        if(major < 4)
            return 500000000;
        else if(major == 4)
            return 800000000;
        else
            return 1500000000;
    } else if(startsWith(hw, "iPad")) {
        string majorMinor = hw.substr(4);
        CCArray& parts = componentsOfString(majorMinor, ',');
        int major = atoi(((CCString*)parts.objectAtIndex(0))->getCString());
        if(major < 2)
            return 500000000;
        else if(major == 2)
            return 800000000;
        else
            return 1500000000;
    } else {
        return 1500000000;
    }
}

bool CCUtils::verifySignature(void* validSign, size_t len) {
    return true;
}

bool CCUtils::isDebugSignature() {
    return false;
}

bool CCUtils::hasExternalStorage() {
    return true;
}

string CCUtils::getInternalStoragePath() {
    NSString* docDir = @"~/Library";
    docDir = [docDir stringByExpandingTildeInPath];
    return [docDir cStringUsingEncoding:NSUTF8StringEncoding];
}

int64_t CCUtils::getAvailableStorageSize() {
    struct statfs buf;
    int64_t freespace = -1;
    if(statfs("/var", &buf) >= 0) {
        freespace = (int64_t)(buf.f_bsize * buf.f_bfree);
    }
    return freespace;
}

string CCUtils::getPackageName() {
	NSBundle* bundle = [NSBundle mainBundle];
    NSString* bundleId = [bundle bundleIdentifier];
    return [bundleId cStringUsingEncoding:NSUTF8StringEncoding];
}

bool CCUtils::isPathExistent(const string& path) {
	// if path is empty, directly return
	if(path.empty())
		return false;
	
	NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
	return [[NSFileManager defaultManager] fileExistsAtPath:nsPath];
}

size_t CCUtils::getFileSize(const string& path) {
    // if path is empty, directly return
    if(!CCUtils::isPathExistent(path))
        return 0;
    
    NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
    NSDictionary* attr = [[NSFileManager defaultManager] attributesOfItemAtPath:nsPath error:nil];
    return [attr[NSFileSize] integerValue];
}

bool CCUtils::createFolder(const string& path) {
	NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
	NSFileManager* fm = [NSFileManager defaultManager];
	return [fm createDirectoryAtPath:nsPath withIntermediateDirectories:YES attributes:NULL error:NULL];
}

string CCUtils::externalize(const string& path) {
    if(!CCFileUtils::sharedFileUtils()->isAbsolutePath(path)) {
        // try append search path to get the exterinal path
        NSString* nsPath = [NSString stringWithUTF8String:path.c_str()];
        NSString* dir = [@"~/Library/" stringByExpandingTildeInPath];
        NSFileManager* fm = [NSFileManager defaultManager];
        const vector<string>& searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        for(vector<string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); iter++) {
            const string& p = *iter;
            NSString* searchPath = [NSString stringWithCString:p.c_str() encoding:NSUTF8StringEncoding];
            NSString* fullpath = [[dir stringByAppendingPathComponent:searchPath] stringByAppendingPathComponent:nsPath];
            if([fm fileExistsAtPath:fullpath]) {
                return [fullpath cStringUsingEncoding:NSUTF8StringEncoding];
            }
        }
        
        // fallback, without search path
        NSString* fullpath = [dir stringByAppendingPathComponent:nsPath];
        return [fullpath cStringUsingEncoding:NSUTF8StringEncoding];
    } else {
        return path;
    }
}

bool CCUtils::deleteFile(const string& path) {
	NSString* p = [NSString stringWithUTF8String:path.c_str()];
	NSFileManager* fm = [NSFileManager defaultManager];
	NSError* error = nil;
	[fm removeItemAtPath:p error:&error];
	return error == nil;
}

string CCUtils::getAppVersion() {
    NSBundle* bundle = [NSBundle mainBundle];
    NSString* ver = [bundle objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSString* build = [bundle objectForInfoDictionaryKey:@"CFBundleVersion"];
    NSString* finalVersion = [NSString stringWithFormat:@"%@.%@", ver, build];
    return [finalVersion cStringUsingEncoding:NSUTF8StringEncoding];
}

string CCUtils::getDeviceType() {
    struct utsname systemInfo;
    uname(&systemInfo);
    char buf[1024];
    sprintf(buf, "%s", systemInfo.machine);
    return buf;
}

string CCUtils::getMacAddress() {
    string mac = "00:00:00:00:00:00";
    char* buf = NULL;
    do {
        // query en0
        int mib[] = {
            CTL_NET,
            AF_ROUTE,
            0,
            AF_LINK,
            NET_RT_IFLIST,
            0
        };
        if ((mib[5] = if_nametoindex("en0")) == 0) {
            break;
        }
        
        // get length of interface struct
        size_t len;
        if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
            break;
        }
        
        // allocate buffer
        if ((buf = (char*)malloc(len * sizeof(char))) == NULL) {
            break;
        }
        
        // get struct
        if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
            break;
        }
        struct if_msghdr* ifm = (struct if_msghdr*)buf;
        struct sockaddr_dl* sdl = (struct sockaddr_dl*)(ifm + 1);
        unsigned char* ptr = (unsigned char*)LLADDR(sdl);
        
        // construct mac string
        char buf2[64];
        sprintf(buf2, "%02x:%02x:%02x:%02x:%02x:%02x",
                *ptr & 0xff,
                *(ptr + 1) & 0xff,
                *(ptr + 2) & 0xff,
                *(ptr + 3) & 0xff,
                *(ptr + 4) & 0xff,
                *(ptr + 5) & 0xff);
        mac = buf2;
    } while(0);

    // free buf
    CC_SAFE_FREE(buf);
    
    // return
    return mac;
}

int CCUtils::getSystemVersionInt() {
    NSString* systemVersion = [[UIDevice currentDevice] systemVersion];
    char buf[16];
    sprintf(buf, "%c", [systemVersion characterAtIndex:0] & 0xff);
    return atoi(buf);
}

void CCUtils::fillScreenBorder(const string& vborder, const string& hborder) {
    const CCRect& rect = CCEGLView::sharedOpenGLView()->getViewPortRect();
    EAGLView* glView = [EAGLView sharedEGLView];
    float scale = [UIScreen mainScreen].scale;
    if(rect.origin.y > 0) {
        // image
        string fullPath = CCUtils::getExternalOrFullPath(vborder);
        NSString* nsFullPath = [NSString stringWithCString:fullPath.c_str() encoding:NSUTF8StringEncoding];
        UIImage* img = [UIImage imageWithContentsOfFile:nsFullPath];
        CGSize imgSize = img.size;
        
        // init frame for image view
        CGRect frame = CGRectZero;
        frame.size.height = rect.origin.y / scale;
        frame.size.width = imgSize.width * frame.size.height / imgSize.height;
        
        // top bar
        while(frame.origin.x < glView.frame.size.width) {
            UIImageView* iv = [[[UIImageView alloc] initWithImage:img] autorelease];
            iv.contentMode = UIViewContentModeScaleAspectFill;
            iv.frame = frame;
            [glView addSubview:iv];
            frame.origin.x += frame.size.width;
        }
        
        // bottom bar
        frame.origin.x = 0;
        frame.origin.y = glView.frame.size.height - frame.size.height;
        while(frame.origin.x < glView.frame.size.width) {
            UIImageView* iv = [[[UIImageView alloc] initWithImage:img] autorelease];
            iv.contentMode = UIViewContentModeScaleAspectFill;
            iv.frame = frame;
            [glView addSubview:iv];
            frame.origin.x += frame.size.width;
        }
    } else if(rect.origin.x > 0) {
        // image
        string fullPath = CCUtils::getExternalOrFullPath(hborder);
        NSString* nsFullPath = [NSString stringWithCString:fullPath.c_str() encoding:NSUTF8StringEncoding];
        UIImage* img = [UIImage imageWithContentsOfFile:nsFullPath];
        CGSize imgSize = img.size;
        
        // init frame for image view
        CGRect frame = CGRectZero;
        frame.size.width = rect.origin.x / scale;
        frame.size.height = imgSize.height * frame.size.width / imgSize.width;
        
        // left bar
        while(frame.origin.y < glView.frame.size.height) {
            UIImageView* iv = [[[UIImageView alloc] initWithImage:img] autorelease];
            iv.contentMode = UIViewContentModeScaleAspectFill;
            iv.frame = frame;
            [glView addSubview:iv];
            frame.origin.y += frame.size.height;
        }
        
        // right bar
        frame.origin.y = 0;
        frame.origin.x = glView.frame.size.width - frame.size.width;
        while(frame.origin.y < glView.frame.size.height) {
            UIImageView* iv = [[[UIImageView alloc] initWithImage:img] autorelease];
            iv.contentMode = UIViewContentModeScaleAspectFill;
            iv.frame = frame;
            [glView addSubview:iv];
            frame.origin.y += frame.size.height;
        }
    }
}

void CCUtils::vibrate() {
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
