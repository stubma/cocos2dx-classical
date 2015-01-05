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
#ifndef __CCMemory_h__
#define __CCMemory_h__

#include "ccMacros.h"
#include <functional>

#ifdef CC_CFLAG_MEMORY_TRACKING

extern "C" CC_DLL void* _ccMalloc(size_t size, const char* file, int line, const char* logTag);
extern "C" CC_DLL void* _ccCalloc(size_t nitems, size_t size, const char* file, int line);
extern "C" CC_DLL void* _ccRealloc(void* ptr, size_t size, const char* file, int line);
extern "C" CC_DLL void _ccFree(void* ptr, const char* file, int line);

inline void* operator new(size_t n, const char* file, int line) {
	return _ccMalloc(n, file, line, "NEW");
}

inline void* operator new[](size_t n, const char* file, int line) {
	return _ccMalloc(n, file, line, "NEW[]");
}

void operator delete(void* p, const char* file, int line) {
	_ccFree(p, file, line);
}

void operator delete(void* p) throw() {
	_ccFree(p, __FILE__, __LINE__);
}

void operator delete[](void* p) throw() {
	_ccFree(p, __FILE__, __LINE__);
}

#define ccMalloc(size) _ccMalloc(size, __FILE__, __LINE__, "MALLOC")
#define ccCalloc(nitems, size) _ccCalloc(nitems, size, __FILE__, __LINE__)
#define ccRealloc(ptr, size) _ccRealloc(ptr, size, __FILE__, __LINE__)
#define ccFree(ptr) _ccFree(ptr, __FILE__, __LINE__)
#define CCNEW new(__FILE__, __LINE__)
#define CCNEWARR(t, s) new(__FILE__, __LINE__) t[(s)]

#else

#define ccMalloc malloc
#define ccCalloc calloc
#define ccRealloc realloc
#define ccFree free
#define CCNEW new
#define CCNEWARR(t, s) new t[(s)]

#endif // #if CC_CFLAG_MEMORY_TRACKING

NS_CC_BEGIN

class CCObject;

/**
 * Memory profile helper class
 */
class CCMemory {    
public:
    /// print a summary memory usage
    static void usageReport();
    
    /// print all leaked memory record
    static void dumpRecord();
    
    /**
     * set what object you want to track, the class you want to track
     * should override getQualifiedName to return a proper class name.
     * we don't want to track all class because it will be slow, it is better
     * to let user specify class names
     */
    static void watchClass(std::function<bool(CCObject*)> func);
    
    /// register CCObject
    static void trackCCObject(CCObject* obj);
    
    /// unregister CCObject
    static void untrackCCObject(CCObject* obj);
    
    /// tracking retain
    static void trackRetain(CCObject* obj, const char* file, int line);
    
    /// tracking release
    static void trackRelease(CCObject* obj, const char* file, int line);
    
    /// tracking autorelease
    static void trackAutorelease(CCObject* obj, const char* file, int line);
};

NS_CC_END

#endif // __CCMemory_h__
