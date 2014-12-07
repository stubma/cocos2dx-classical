/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-better
 
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

#include "CCCalendar.h"
#include "support/utils/CCUtils.h"
#import <Foundation/Foundation.h>

NS_CC_BEGIN

CCCalendar* CCCalendar::s_instance = NULL;

CCCalendar::CCCalendar() {
    m_time = (double)CCUtils::currentTimeMillis() / 1000.0f;
}

CCCalendar::~CCCalendar() {
    s_instance = NULL;
}

CCCalendar* CCCalendar::sharedCalendar() {
    if(!s_instance) {
        s_instance = new CCCalendar();
    }
    return s_instance;
}

void CCCalendar::setNow() {
    m_time = (double)CCUtils::currentTimeMillis() / 1000.0f;
}

int CCCalendar::getYear() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSYearCalendarUnit fromDate:d];
    return (int)dc.year;
}

int CCCalendar::getMonth() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSMonthCalendarUnit fromDate:d];
    return (int)dc.month;
}

int CCCalendar::getDay() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSDayCalendarUnit fromDate:d];
    return (int)dc.day;
}

int CCCalendar::getWeekday() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSWeekdayCalendarUnit fromDate:d];
    return (int)dc.weekday;
}

int CCCalendar::getHour() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSHourCalendarUnit fromDate:d];
    return (int)dc.hour;
}

int CCCalendar::getMinute() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSMinuteCalendarUnit fromDate:d];
    return (int)dc.minute;
}

int CCCalendar::getSecond() {
    NSCalendar* c = [NSCalendar currentCalendar];
    NSDate* d = [NSDate dateWithTimeIntervalSince1970:m_time];
    NSDateComponents* dc = [c components:NSSecondCalendarUnit fromDate:d];
    return (int)dc.second;
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS