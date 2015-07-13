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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "CCLocale.h"
#include "ccTypes.h"

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
    // get default locale
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "java/util/Locale", "getDefault", "()Ljava/util/Locale;");
    jobject jLocale = t.env->CallStaticObjectMethod(t.classID, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get language
    JniHelper::getMethodInfo(t, "java/util/Locale", "getLanguage", "()Ljava/lang/String;");
    jstring jLan = (jstring)t.env->CallObjectMethod(jLocale, t.methodID);
    string ret = JniHelper::jstring2string(jLan);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // return
    return ret;
}

string CCLocale::getCountry() {
    // get default locale
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "java/util/Locale", "getDefault", "()Ljava/util/Locale;");
    jobject jLocale = t.env->CallStaticObjectMethod(t.classID, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get language
    JniHelper::getMethodInfo(t, "java/util/Locale", "getCountry", "()Ljava/lang/String;");
    jstring jCty = (jstring)t.env->CallObjectMethod(jLocale, t.methodID);
    string ret = JniHelper::jstring2string(jCty);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // return
    return ret;
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID