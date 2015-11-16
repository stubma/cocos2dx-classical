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
#include "support/codec/CCMD5.h"
#include "support/codec/MD5.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
	
NS_CC_BEGIN

string CCMD5::md5(const char* s) {
	// return empty for a empty source
	if(!s || strlen(s) <= 0)
		return "";

	// update md5
    MD5 md5(s);

	// return hex md5 string
    return md5.hexdigest();
}

string CCMD5::md5(const void* data, size_t len) {
	// update md5
    MD5 md5;
    md5.update((const char *)data, (MD5::size_type)len);

    // return hex md5 string
    return md5.hexdigest();
}
	
NS_CC_END
