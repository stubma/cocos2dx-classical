#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

class BaseClass {
public:
	virtual void haha() = 0;
};

class SimpleNativeClass : public BaseClass
{
public:
	SimpleNativeClass();
	virtual void processString(int s);
	void method1();
};

#endif
