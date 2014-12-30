#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

class BaseClass {
public:
	virtual void haha() = 0;
};

class BaseClass2 {
public:
	virtual void haha2();
};

class SimpleNativeClass : public BaseClass, public BaseClass2
{
public:
	SimpleNativeClass();
	virtual void processString(int s);
	void method1();
	virtual void haha();
};

#endif
