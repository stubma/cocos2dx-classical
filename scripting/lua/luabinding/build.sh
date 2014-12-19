#!/bin/bash
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

cd "$DIR/"
./tolua++ -L basic.lua -o "../cocos2dx_support/LuaCocos2d.cpp" Cocos2d.tolua