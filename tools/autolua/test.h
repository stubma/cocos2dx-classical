#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

#include <string>

namespace cocos2d {
typedef struct {
	int i;
} CCPoint;
}

class SimpleNativeClass
{
public:
	static void processInt(cocos2d::CCPoint f);
};

#endif
