#!/bin/bash
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

cd "$DIR/"
./tolua++ -L basic.lua -n cocos2d -o "../cocos2dx_support/lua_cocos2d_auto.cpp" cocos2d.tolua