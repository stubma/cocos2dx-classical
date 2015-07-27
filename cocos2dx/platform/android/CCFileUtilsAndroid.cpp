/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

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

#include "CCFileUtilsAndroid.h"
#include "support/zip/ZipUtils.h"
#include "platform/CCCommon.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "jni/JniHelper.h"
#include "CCUtilsAndroid.h"

using namespace std;

NS_CC_BEGIN

// record the zip on the resource path
static ZipFile *s_pZipFile = NULL;
static ZipFile *s_pMainXApkFile = NULL;
static ZipFile *s_pPatchXApkFile = NULL;
static std::vector<std::string> s_strvec;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsAndroid();
        s_sharedFileUtils->init();
        string resourcePath = getApkPath();
        s_pZipFile = new ZipFile(resourcePath, "assets/");
    }
    return s_sharedFileUtils;
}

CCFileUtilsAndroid::CCFileUtilsAndroid() :
m_mainApkExpansionEnabled(false),
m_patchApkExpansionEnabled(false)
{
}

CCFileUtilsAndroid::~CCFileUtilsAndroid()
{
    CC_SAFE_DELETE(s_pZipFile);
    CC_SAFE_DELETE(s_pMainXApkFile);
    CC_SAFE_DELETE(s_pPatchXApkFile);
}

bool CCFileUtilsAndroid::init()
{
    m_strDefaultResRootPath = "assets/";
    return CCFileUtils::init();
}

void CCFileUtilsAndroid::enableMainApkExpansion(int versionCode) {
    // open main expansion
    string xapkPath = CCUtilsAndroid::getMainExpansionPath(versionCode);
    s_pMainXApkFile = new ZipFile(xapkPath, "assets/");
    
    // set flag
    m_mainApkExpansionEnabled = true;
    
    // init java side
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "initMainApkExpansion", "(I)V");
    t.env->CallStaticVoidMethod(t.classID, t.methodID, versionCode);
    
    // release
    t.env->DeleteLocalRef(t.classID);
}

void CCFileUtilsAndroid::enablePatchApkExpansion(int versionCode) {
    // ensure old pointer is released
    CC_SAFE_DELETE(s_pPatchXApkFile);
    
    // open patch expansion
    string xapkPath = CCUtilsAndroid::getPatchExpansionPath(versionCode);
    s_pPatchXApkFile = new ZipFile(xapkPath, "assets/");
    
    // set flag
    m_patchApkExpansionEnabled = true;
    
    // init java side
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "initPatchApkExpansion", "(I)V");
    t.env->CallStaticVoidMethod(t.classID, t.methodID, versionCode);
    
    // release
    t.env->DeleteLocalRef(t.classID);
}

const std::vector<std::string>& CCFileUtilsAndroid::listAssets(const std::string& subpath) {
    // clear
    s_strvec.clear();
    
    // helper struct
    JniMethodInfo t;

    // entries array
    jobjectArray items = NULL;
    
    // jni string subpath
    jstring jSubpath = NULL;
    
    // try expansion first, then apk file
    if(m_mainApkExpansionEnabled || m_patchApkExpansionEnabled) {
        // get asset manager
        JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "listXApk", "(Ljava/lang/String;)[Ljava/lang/String;");
        jSubpath = t.env->NewStringUTF(subpath.c_str());
        items = (jobjectArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, jSubpath);
        
        // release
        t.env->DeleteLocalRef(t.classID);
    } else {
        // get asset manager
        JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "getAssetManager", "()Landroid/content/res/AssetManager;");
        jobject am = t.env->CallStaticObjectMethod(t.classID, t.methodID);
        
        // release
        t.env->DeleteLocalRef(t.classID);
        
        // get list and call it
        JniHelper::getMethodInfo(t, "android/content/res/AssetManager", "list", "(Ljava/lang/String;)[Ljava/lang/String;");
        jSubpath = t.env->NewStringUTF(subpath.c_str());
        items = (jobjectArray)t.env->CallObjectMethod(am, t.methodID, jSubpath);
        
        // release
        t.env->DeleteLocalRef(t.classID);
    }
    
    // add to vector
    if(items) {
        jsize size = t.env->GetArrayLength(items);
        for(jsize i = 0; i < size; i++) {
            jstring item = (jstring)t.env->GetObjectArrayElement(items, i);
            s_strvec.push_back(JniHelper::jstring2string(item));
            t.env->DeleteLocalRef(item);
        }
    }
    
    // common release
    if(items) {
        t.env->DeleteLocalRef(items);
    }
    if(jSubpath) {
        t.env->DeleteLocalRef(jSubpath);
    }
    
    // return
    return s_strvec;
}

bool CCFileUtilsAndroid::isFileExist(const std::string& strFilePath)
{
    if (0 == strFilePath.length())
    {
        return false;
    }

    bool bFound = false;
    
    // Check whether file exists in apk.
    if (strFilePath[0] != '/')
    {
        std::string strPath = strFilePath;
        if (strPath.find(m_strDefaultResRootPath) != 0)
        {// Didn't find "assets/" at the beginning of the path, adding it.
            strPath.insert(0, m_strDefaultResRootPath);
        }
        
        if(s_pPatchXApkFile && s_pPatchXApkFile->fileExists(strPath)) {
            bFound = true;
        } else if(s_pMainXApkFile && s_pMainXApkFile->fileExists(strPath)) {
            bFound = true;
        } else if(s_pZipFile->fileExists(strPath)) {
            bFound = true;
        } 
    }
    else
    {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if(fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool CCFileUtilsAndroid::isAbsolutePath(const std::string& strPath)
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/' || strPath.find(m_strDefaultResRootPath) == 0)
    {
        return true;
    }
    return false;
}


unsigned char* CCFileUtilsAndroid::getFileData(const char* pszFileName, const char* pszMode, size_t* pSize)
{    
    return doGetFileData(pszFileName, pszMode, pSize, false);
}

unsigned char* CCFileUtilsAndroid::getFileDataForAsync(const char* pszFileName, const char* pszMode, size_t* pSize)
{
    return doGetFileData(pszFileName, pszMode, pSize, true);
}

unsigned char* CCFileUtilsAndroid::doGetFileData(const char* pszFileName, const char* pszMode, size_t* pSize, bool forAsync)
{
    unsigned char * pData = 0;
    
    if ((! pszFileName) || (! pszMode) || 0 == strlen(pszFileName))
    {
        return 0;
    }
    
    string fullPath = fullPathForFilename(pszFileName);
    
    if (fullPath[0] != '/')
    {
        if (forAsync)
        {
            if(s_pPatchXApkFile) {
                pData = s_pPatchXApkFile->getFileData(fullPath.c_str(), pSize, s_pPatchXApkFile->_dataThread);
            }
            if(!pData && s_pMainXApkFile) {
                pData = s_pMainXApkFile->getFileData(fullPath.c_str(), pSize, s_pMainXApkFile->_dataThread);
            }
            if(!pData) {
                pData = s_pZipFile->getFileData(fullPath.c_str(), pSize, s_pZipFile->_dataThread);
            }
        }
        else
        {
            if(s_pPatchXApkFile) {
                pData = s_pPatchXApkFile->getFileData(fullPath.c_str(), pSize);
            }
            if(!pData && s_pMainXApkFile) {
                pData = s_pMainXApkFile->getFileData(fullPath.c_str(), pSize);
            }
            if(!pData) {
                pData = s_pZipFile->getFileData(fullPath.c_str(), pSize);
            }
        }
    }
    else
    {
        do
        {
            // read rrom other path than user set it
	        //CCLOG("GETTING FILE ABSOLUTE DATA: %s", pszFileName);
            FILE *fp = fopen(fullPath.c_str(), pszMode);
            CC_BREAK_IF(!fp);
            
            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);
            
            if (pSize)
            {
                *pSize = size;
            }
        } while (0);
    }
    
    if (! pData)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        CCLOG("%s", msg.c_str());
    }
    
    return pData;
}

string CCFileUtilsAndroid::getWritablePath()
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = getFileDirectoryJNI();

    if (tmp.length() > 0)
    {
        dir.append(tmp).append("/");

        return dir;
    }
    else
    {
        return "";
    }
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID