#include "CCUtilsIOS.h"

NS_CC_BEGIN

UIViewController* CCUtilsIOS::findViewController(UIView* view) {
    for (UIView* next = [view superview]; next; next = next.superview) {
        UIResponder* nextResponder = [next nextResponder];
        if ([nextResponder isKindOfClass:[UIViewController class]]) {
            return (UIViewController*)nextResponder;
        }
    }
    
    // try window root view controller
    for (UIView* next = [view superview]; next; next = next.superview) {
        if([next isKindOfClass:[UIWindow class]]) {
            return ((UIWindow*)next).rootViewController;
        }
    }
    
    return nil;
}

NS_CC_END