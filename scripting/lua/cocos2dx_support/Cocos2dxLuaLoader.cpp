/****************************************************************************
Copyright (c) 2011 cocos2d-x.org

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
#include "Cocos2dxLuaLoader.h"
#include <string>
#include <algorithm>
#include "support/utils/CCUtils.h"

using namespace cocos2d;

extern "C"
{
    int cocos2dx_lua_loader(lua_State *L) {
        // remove lua/lc extension
        std::string filepath(luaL_checkstring(L, 1));
        size_t pos = filepath.rfind(".lua");
        if (pos != std::string::npos) {
            filepath = filepath.substr(0, pos);
        }
        pos = filepath.rfind(".lc");
        if (pos != std::string::npos) {
            filepath = filepath.substr(0, pos);
        }
        
        // convert package to path, for example: cc.XX will be cc/XX
        std::string filename = CCUtils::lastPathComponent(filepath);
        pos = filename.find_first_of(".");
        while (pos != std::string::npos) {
            filename.replace(pos, 1, "/");
            pos = filename.find_first_of(".");
        }
        string basepath = CCUtils::deleteLastPathComponent(filepath);
        string filepathWithoutExt = CCUtils::appendPathComponent(basepath, filename);
        
        // find script relative path
        pos = filepathWithoutExt.rfind("script/");
        if(pos != std::string::npos) {
            filepathWithoutExt = filepathWithoutExt.substr(pos);
        }
        
        // try find compiled lua first
        // then try find lua source
        filepath = filepathWithoutExt + ".lc";
        filepath = CCUtils::getExternalOrFullPath(filepath);
        if(!CCUtils::isPathExistent(filepath)) {
            filepath = filepathWithoutExt + ".lua";
            filepath = CCUtils::getExternalOrFullPath(filepath);
        }
        
        // load lua file
        unsigned long codeBufferSize = 0;
        unsigned char* codeBuffer = CCFileUtils::sharedFileUtils()->getFileData(filepath.c_str(), "rb", &codeBufferSize);
        if (codeBuffer) {
            if (luaL_loadbuffer(L, (char*)codeBuffer, codeBufferSize, filepath.c_str()) != 0) {
                luaL_error(L, "error loading module %s from file %s :\n\t%s",
                    lua_tostring(L, 1), filepath.c_str(), lua_tostring(L, -1));
            }
            delete[] codeBuffer;
        } else {
            CCLOG("can not get file data of %s", filepath.c_str());
        }
        
        return 1;
    }
}
