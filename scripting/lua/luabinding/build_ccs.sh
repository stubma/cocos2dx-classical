#!/bin/bash
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

cd "$DIR/"
./tolua++ -L basic_ccs.lua -o "../cocos2dx_support/lua_CocoStudio_auto.cpp" CocoStudio.tolua
