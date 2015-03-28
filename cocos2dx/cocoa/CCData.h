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
#ifndef __CCData__
#define __CCData__

#include "ccTypes.h"

NS_CC_BEGIN

/**
 * A class which is similar with NSData, it manages a block of memory.
 * It uses CB prefix because cocos2d-x has a CCData in CCBReader extension
 */
class CC_DLL CCData : public CCObject {
public:
    CCData();
    CCData(uint8_t* bytes, size_t size);
    CCData(CCData* data);
    virtual ~CCData();
    
    static CCData* create();
    static CCData* createWithBytes(uint8_t* bytes, size_t size);
    static CCData* createWithData(CCData* data);
    
    void appendData(CCData* data);
    void appendBytes(uint8_t* bytes, size_t size);
    
    CC_SYNTHESIZE(uint8_t*, m_bytes, Bytes);
    CC_SYNTHESIZE(size_t, m_size, Size);
};

NS_CC_END

#endif // __CCData__
