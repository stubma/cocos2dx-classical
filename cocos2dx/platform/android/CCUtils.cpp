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

#include "CCUtils.h"
#include <jni.h>
#include "JniHelper.h"
#include "CCLocale.h"
#include "support/codec/CCMD5.h"
#include "ccTypes.h"
#include "ccMacros.h"
#include "CCUtilsAndroid.h"
#include <unistd.h>
#include <sys/stat.h>
#include "platform/android/CCFileUtilsAndroid.h"

NS_CC_BEGIN

static string gInternalStoragePath = "";

bool CCUtils::deleteFile(const string& path) {
	return unlink(path.c_str()) == 0;
}

bool CCUtils::createFolder(const string& path) {
	return mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == 0;
}

bool CCUtils::isPathExistent(const string& path) {
	// if path is empty, directly return
	if(path.empty())
		return false;
    
    // if relative path, convert to assets path and check
    // we can't use CCFileUtils::isAbsolutePath because android file utils
    // treat path starts with assets/ is absolute
    if(path[0] == '/') {
        return access(path.c_str(), 0) == 0;
    } else {
        return CCFileUtils::sharedFileUtils()->isFileExist(path);
    }
}

size_t CCUtils::getFileSize(const string& path) {
    if(!CCUtils::isPathExistent(path)) {
        return 0;
    }
    
    struct stat st;
    if(stat(path.c_str(), &st) == 0) {
        return st.st_size;
    }
    return 0;
}

string CCUtils::externalize(const string& path) {
    if(!CCFileUtils::sharedFileUtils()->isAbsolutePath(path)) {
        // ensure internal dir ends with slash
        string internalStorage = getInternalStoragePath();
        if(internalStorage[internalStorage.length() - 1] != '/') {
            internalStorage += "/";
        }
        
        // append search path
        const vector<string>& searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        for(vector<string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); iter++) {
            string fullpath = internalStorage + (*iter) + path;
            if(isPathExistent(fullpath)) {
                return fullpath;
            }
        }
        
        // fallback, without search path
        return internalStorage + path;
    } else {
        return path;
    }
}

string CCUtils::getPackageName() {
	// get context
    jobject ctx = CCUtilsAndroid::getContext();

    // get package manager
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Context", "getPackageManager", "()Landroid/content/pm/PackageManager;");
	jobject packageManager = t.env->CallObjectMethod(ctx, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);

	// get package name
    JniHelper::getMethodInfo(t, "android/content/Context", "getPackageName", "()Ljava/lang/String;");
	jstring packageName = (jstring)t.env->CallObjectMethod(ctx, t.methodID);

	// get c++ string
	const char* cpn = (const char*)t.env->GetStringUTFChars(packageName, NULL);
	string pn = cpn;

	// release
	t.env->ReleaseStringUTFChars(packageName, cpn);
    t.env->DeleteLocalRef(t.classID);

	// return
	return pn;
}

string CCUtils::getInternalStoragePath() {
    if(gInternalStoragePath.empty()) {
        // get context
        jobject ctx = CCUtilsAndroid::getContext();
        
        // get file dir
        JniMethodInfo t;
        JniHelper::getMethodInfo(t, "android/content/Context", "getFilesDir", "()Ljava/io/File;");
        jobject file = t.env->CallObjectMethod(ctx, t.methodID);
        
        // release
        t.env->DeleteLocalRef(t.classID);
        
        // get absolute path
        JniHelper::getMethodInfo(t, "java/io/File", "getAbsolutePath", "()Ljava/lang/String;");
        jstring path = (jstring)t.env->CallObjectMethod(file, t.methodID);
        
        // get c++ string
        gInternalStoragePath = path ? JniHelper::jstring2string(path) : "/";
        
        // release
        t.env->DeleteLocalRef(path);
        t.env->DeleteLocalRef(file);
        t.env->DeleteLocalRef(t.classID);
    }
   
    // return
    return gInternalStoragePath;
}

bool CCUtils::hasExternalStorage() {
    // get state
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "android/os/Environment", "getExternalStorageState", "()Ljava/lang/String;");
    jobject jState = t.env->CallStaticObjectMethod(t.classID, t.methodID);

    // get mount state
    jfieldID fid = t.env->GetStaticFieldID(t.classID, "MEDIA_MOUNTED", "Ljava/lang/String;");
    jstring jMounted = (jstring)t.env->GetStaticObjectField(t.classID, fid);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // is same?
    JniHelper::getMethodInfo(t, "java/lang/Object", "equals", "(Ljava/lang/Object;)Z");
    bool ret = t.env->CallBooleanMethod(jMounted, t.methodID, jState);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // return
    return ret;
}

int64_t CCUtils::getAvailableStorageSize() {
    // actually we returned internal storage size
    string path = getInternalStoragePath();
    
    // get statfs
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/os/StatFs", "<init>", "(Ljava/lang/String;)V");
    jstring jPath = t.env->NewStringUTF(path.c_str());
    jobject statfs = t.env->NewObject(t.classID, t.methodID, jPath);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get block size
    JniHelper::getMethodInfo(t, "android/os/StatFs", "getBlockSize", "()I");
    jint blockSize = t.env->CallIntMethod(statfs, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get available block count
    JniHelper::getMethodInfo(t, "android/os/StatFs", "getAvailableBlocks", "()I");
    jint blocks = t.env->CallIntMethod(statfs, t.methodID);
    
    // release
    t.env->DeleteLocalRef(jPath);
    t.env->DeleteLocalRef(t.classID);
    
    // return
    return blockSize * blocks;
}

static jbyteArray getFirstSignatureBytes() {
    // get context
    jobject ctx = CCUtilsAndroid::getContext();

    // get package manager
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Context", "getPackageManager", "()Landroid/content/pm/PackageManager;");
	jobject packageManager = t.env->CallObjectMethod(ctx, t.methodID);

    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get package name
    JniHelper::getMethodInfo(t, "android/content/Context", "getPackageName", "()Ljava/lang/String;");
	jstring packageName = (jstring)t.env->CallObjectMethod(ctx, t.methodID);

    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get package info
    JniHelper::getMethodInfo(t, "android/content/pm/PackageManager", "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
	jint flags = t.env->GetStaticIntField(t.classID, t.env->GetStaticFieldID(t.classID, "GET_SIGNATURES", "I"));
	jobject packageInfo = t.env->CallObjectMethod(packageManager, t.methodID, packageName, flags);
    
    // get first signature java object
	jclass klazz = t.env->GetObjectClass(packageInfo);
	jobjectArray signatures = (jobjectArray)t.env->GetObjectField(packageInfo,
                                                                  t.env->GetFieldID(klazz, "signatures", "[Landroid/content/pm/Signature;"));
	jobject signature = t.env->GetObjectArrayElement(signatures, 0);

    // get byte array of signature
	klazz = t.env->GetObjectClass(signature);
    t.methodID = t.env->GetMethodID(klazz, "toByteArray", "()[B");
	jbyteArray certificate = (jbyteArray)t.env->CallObjectMethod(signature, t.methodID);

    // release
    t.env->DeleteLocalRef(packageManager);
    t.env->DeleteLocalRef(packageName);
    t.env->DeleteLocalRef(packageInfo);
    t.env->DeleteLocalRef(signatures);
    t.env->DeleteLocalRef(signature);
    t.env->DeleteLocalRef(klazz);
    t.env->DeleteLocalRef(t.classID);

    // return
    return certificate;
}

bool CCUtils::isDebugSignature() {
	// get sig data
    jbyteArray certificate = getFirstSignatureBytes();

    // create input stream
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "java/io/ByteArrayInputStream", "<init>", "([B)V");
    jobject bais = t.env->NewObject(t.classID, t.methodID, certificate);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // cert factory
    JniHelper::getStaticMethodInfo(t, "java/security/cert/CertificateFactory", "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring protocol = t.env->NewStringUTF("X.509");
    jobject cf = t.env->CallStaticObjectMethod(t.classID, t.methodID, protocol);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // cert
    JniHelper::getMethodInfo(t, "java/security/cert/CertificateFactory", "generateCertificate", "(Ljava/io/InputStream;)Ljava/security/cert/Certificate;");
    jobject cert = t.env->CallObjectMethod(cf, t.methodID, bais);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // issuer dn
    JniHelper::getMethodInfo(t, "java/security/cert/X509Certificate", "getIssuerDN", "()Ljava/security/Principal;");
    jobject ip = t.env->CallObjectMethod(cert, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // issuer dn name
    JniHelper::getMethodInfo(t, "java/security/Principal", "getName", "()Ljava/lang/String;");
    jstring ipn = (jstring)t.env->CallObjectMethod(ip, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);

    // check issuer dn name
    bool debug = false;
    string sub = "Android Debug";
    string cppipn = JniHelper::jstring2string(ipn);
    if(cppipn.find(sub) != string::npos) {
        debug = true;
    }

    // check more?
    if(!debug) {
        // subject dn
        JniHelper::getMethodInfo(t, "java/security/cert/X509Certificate", "getSubjectDN", "()Ljava/security/Principal;");
        jobject sp = t.env->CallObjectMethod(cert, t.methodID);
        
        // release
        t.env->DeleteLocalRef(t.classID);

        // subject dn name
        JniHelper::getMethodInfo(t, "java/security/Principal", "getName", "()Ljava/lang/String;");
        jstring spn = (jstring)t.env->CallObjectMethod(sp, t.methodID);
        
        // release
        t.env->DeleteLocalRef(t.classID);

        // check
        string cppspn = JniHelper::jstring2string(spn);
        if(cppspn.find(sub) != string::npos) {
            debug = true;
        }

        // release
        t.env->DeleteLocalRef(sp);
        t.env->DeleteLocalRef(spn);
    }

    // release
    t.env->DeleteLocalRef(bais);
    t.env->DeleteLocalRef(certificate);
    t.env->DeleteLocalRef(cf);
    t.env->DeleteLocalRef(protocol);
    t.env->DeleteLocalRef(cert);
    t.env->DeleteLocalRef(ip);
    t.env->DeleteLocalRef(ipn);

    // return
    return debug;
}

bool CCUtils::verifySignature(void* validSign, size_t len) {
	// basic check
	if(!validSign)
		return true;

	// get sig data
    jbyteArray certificate = getFirstSignatureBytes();

	// md5
    JNIEnv* env = CCUtilsAndroid::getJNIEnv();
	bool valid = true;
	jsize cLen = env->GetArrayLength(certificate);
	jbyte* cData = env->GetByteArrayElements(certificate, JNI_FALSE);
	if (cLen > 0) {
		string md5 = CCMD5::md5(cData, cLen);
        size_t md5Len = md5.length();
		if(md5Len != len) {
			valid = false;
		} else {
			char* p = (char*)validSign;
			for(size_t i = 0; i < md5Len; i++) {
				if(md5[i] != p[i]) {
					valid = false;
					break;
				}
			}
		}
	}

	// release
	env->ReleaseByteArrayElements(certificate, cData, 0);
    env->DeleteLocalRef(certificate);

	// return
	return valid;
}

int CCUtils::getCpuHz() {
    // get package manager
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "getCPUFrequencyMax", "()I");
	int ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // return
    return ret;
}

void CCUtils::openUrl(const string& url) {
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "openUrl", "(Ljava/lang/String;)V");
    jstring jUrl = t.env->NewStringUTF(url.c_str());
	t.env->CallStaticVoidMethod(t.classID, t.methodID, jUrl);
    
    // release
    t.env->DeleteLocalRef(t.classID);
}

void CCUtils::openAppInStore(const string& appId) {
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "openAppInStore", "()V");
	t.env->CallStaticVoidMethod(t.classID, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
}

void CCUtils::showSystemConfirmDialog(const char* title, const char* msg, const char* positiveButton, const char* negativeButton, CCCallFunc* onOK, CCCallFunc* onCancel) {
    // find method
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t,
                                   "org/cocos2dx/lib/CCUtils",
                                   "showConfirmDialog",
                                   "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JJ)V");

	// create jstring
	jstring jTitle = title ? t.env->NewStringUTF(title) : NULL;
	jstring jMsg = msg ? t.env->NewStringUTF(msg) : NULL;
	jstring jPositiveButton = positiveButton ? t.env->NewStringUTF(positiveButton) : NULL;
	jstring jNegativeButton = negativeButton ? t.env->NewStringUTF(negativeButton) : NULL;

	// call java side
    t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle, jMsg, jPositiveButton, jNegativeButton, (jlong)onOK, (jlong)onCancel);

	// delete reference
	if(jTitle)
		t.env->DeleteLocalRef(jTitle);
	if(jMsg)
		t.env->DeleteLocalRef(jMsg);
    if(jPositiveButton)
        t.env->DeleteLocalRef(jPositiveButton);
    if(jNegativeButton)
        t.env->DeleteLocalRef(jNegativeButton);
    t.env->DeleteLocalRef(t.classID);
}

string CCUtils::getAppVersion() {
    // get context
    jobject ctx = CCUtilsAndroid::getContext();
    
    // get package manager
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Context", "getPackageManager", "()Landroid/content/pm/PackageManager;");
	jobject packageManager = t.env->CallObjectMethod(ctx, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
    
    // get package info
    JniHelper::getMethodInfo(t, "android/content/pm/PackageManager", "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    string pn = getPackageName();
    jstring jPN = t.env->NewStringUTF(pn.c_str());
	jobject packageInfo = t.env->CallObjectMethod(packageManager, t.methodID, jPN, 0);
    
    // get version
    jclass piClass = t.env->GetObjectClass(packageInfo);
    jstring jVer = (jstring)t.env->GetObjectField(packageInfo, t.env->GetFieldID(piClass, "versionName", "Ljava/lang/String;"));
    string ver = JniHelper::jstring2string(jVer);
                                           
    // release
    t.env->DeleteLocalRef(packageManager);
    t.env->DeleteLocalRef(packageInfo);
    t.env->DeleteLocalRef(piClass);
    t.env->DeleteLocalRef(jVer);
    t.env->DeleteLocalRef(jPN);
    t.env->DeleteLocalRef(t.classID);
    
    return ver;
}

string CCUtils::getDeviceType() {
	JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "getDeviceType", "()Ljava/lang/String;");
	jstring jDevice = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	string device = JniHelper::jstring2string(jDevice);
	t.env->DeleteLocalRef(jDevice);
    t.env->DeleteLocalRef(t.classID);
	return device;
}

string CCUtils::getMacAddress() {
	JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "getMacAddress", "()Ljava/lang/String;");
	jstring jMac = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	string mac = JniHelper::jstring2string(jMac);
	t.env->DeleteLocalRef(jMac);
    t.env->DeleteLocalRef(t.classID);
	return mac;
}

int CCUtils::getSystemVersionInt() {
	JNIEnv* env = CCUtilsAndroid::getJNIEnv();
	jclass clazz = env->FindClass("android/os/Build$VERSION");
	jfieldID fid = env->GetStaticFieldID(clazz, "SDK_INT", "I");
	int v = env->GetStaticIntField(clazz, fid);
	env->DeleteLocalRef(clazz);
	return v;
}

void CCUtils::fillScreenBorder(const string& vborder, const string& hborder) {
    // get package manager
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "fillScreenBorder", "(Ljava/lang/String;Ljava/lang/String;)V");
    jstring jVBorder = t.env->NewStringUTF(vborder.c_str());
    jstring jHBorder = t.env->NewStringUTF(hborder.c_str());
    t.env->CallStaticVoidMethod(t.classID, t.methodID, jVBorder, jHBorder);
    
    // release
    t.env->DeleteLocalRef(jVBorder);
    t.env->DeleteLocalRef(jHBorder);
    t.env->DeleteLocalRef(t.classID);
}

void CCUtils:vibrate() {
    // get package manager
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/CCUtils", "vibrate", "()V");
    t.env->CallStaticVoidMethod(t.classID, t.methodID);
    
    // release
    t.env->DeleteLocalRef(t.classID);
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
