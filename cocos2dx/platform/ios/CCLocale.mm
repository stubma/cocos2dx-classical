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
#include "CCLocale.h"
#import <Foundation/Foundation.h>

NS_CC_BEGIN

CCLocale* CCLocale::s_instance = NULL;

CCLocale::CCLocale() {
}

CCLocale::~CCLocale() {
    s_instance = NULL;
}

CCLocale* CCLocale::sharedLocale() {
    if(!s_instance) {
        s_instance= new CCLocale();
    }
    return s_instance;
}

string CCLocale::getISOLanguage() {
    string lan = getLanguage();
    if(lan.length() > 2)
        lan = lan.substr(0, 2);
    return lan;
}

string CCLocale::getLanguage() {
    // get language
    NSString* lan = [[NSLocale preferredLanguages] objectAtIndex:0];
    if(!lan)
        return "en";
    else
        return [lan cStringUsingEncoding:NSUTF8StringEncoding];
}

string CCLocale::getCountry() {
    // get country
    NSString* c = [[NSLocale currentLocale] objectForKey:NSLocaleCountryCode];
    if(!c)
        return "US";
    else
        return [c cStringUsingEncoding:NSUTF8StringEncoding];
}

NS_CC_END