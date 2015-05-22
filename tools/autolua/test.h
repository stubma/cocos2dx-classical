#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

#include <string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

namespace cocos2d {

class SimpleNativeClass
{
public:
    static SimpleNativeClass* create(CCNode* normalSprite, CCNode* focusSprite = NULL);
};

}

#endif