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
#include "CCData.h"

NS_CC_BEGIN

CCData::CCData() {
    m_size = 0;
    m_bytes = (uint8_t*)malloc(m_size * sizeof(uint8_t));
}

CCData::CCData(uint8_t* bytes, size_t size) {
    m_size = size;
    m_bytes = (uint8_t*)malloc(m_size * sizeof(uint8_t));
    memcpy(m_bytes, bytes, m_size);
}

CCData::CCData(CCData* data) {
    m_size = data->m_size;
    m_bytes = (uint8_t*)malloc(m_size * sizeof(uint8_t));
    memcpy(m_bytes, data->m_bytes, m_size);
}

CCData::~CCData() {
    CC_SAFE_FREE(m_bytes);
}

CCData* CCData::create() {
    CCData* d = new CCData();
    CC_SAFE_AUTORELEASE_RETURN(d, CCData*);
}

CCData* CCData::createWithBytes(uint8_t* bytes, size_t size) {
    CCData* d = new CCData(bytes, size);
    CC_SAFE_AUTORELEASE_RETURN(d, CCData*);
}

CCData* CCData::createWithData(CCData* data) {
    CCData* d = new CCData(data);
    CC_SAFE_AUTORELEASE_RETURN(d, CCData*);
}

void CCData::appendData(CCData* data) {
    appendBytes(data->getBytes(), data->getSize());
}

void CCData::appendBytes(uint8_t* bytes, size_t size) {
    m_size += size;
    m_bytes = (uint8_t*)realloc(m_bytes, m_size);
    memcpy(m_bytes + m_size - size, bytes, size);
}

NS_CC_END
