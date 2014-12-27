#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

#include <string>
#include <stdint.h>
#include "cocos2d.h"

USING_NS_CC;

enum someThingEnumerated {
	kValue1 = 1,
	kValue2,
	kValue3,
	kValue4
};

class CC_DLL SimpleNativeClass : public CCNode
{
protected:
	int m_someField;
	char* m_anotherMoreComplexField;

public:
	CREATE_FUNC(SimpleNativeClass)
    static const uint32_t OBJECT_TYPE = 0x777;
    int m_someOtherField;
    virtual uint32_t getObjectType() {
        return SimpleNativeClass::OBJECT_TYPE;
    };

    SimpleNativeClass();
	SimpleNativeClass(int m) : m_someField(m) {};
	SimpleNativeClass(int m1, int m2) : m_someField(m1), m_someOtherField(m2) {};
	virtual ~SimpleNativeClass();
	virtual bool init();

	// these methods are simple, can be defined inline
	int getSomeField(someThingEnumerated func) {
		return m_someField;
	}
	const int& getSomeOtherField() {
		return m_someOtherField;
	}
	const char *getAnotherMoreComplexField() {
		return m_anotherMoreComplexField;
	}
	void setSomeField(const int& f) {
		m_someField = f;
	}
	void setSomeField() {

	}
	void setSomeOtherField(int f) {
		m_someOtherField = f;
	}
	void setAnotherMoreComplexField(const char *str);

	long long thisReturnsALongLong();

	static void func();
	static void func(int a);

protected:
	static void func(int a, float b);

private:
	long long receivesLongLong(long long someId);
	std::string returnsAString();
	const char *returnsACString();

	int doSomeProcessing(std::string arg1, std::string arg2);

	CC_SYNTHESIZE(int, m_age, Age);
};

namespace SomeNamespace {
class AnotherClass {
protected:
	int justOneField;

public:
    static const uint32_t OBJECT_TYPE = 0x778;
    virtual uint32_t getObjectType() {
        return AnotherClass::OBJECT_TYPE;
    };
	int aPublicField;

	AnotherClass();
	~AnotherClass();

	// also simple methods, can be defined inline
	int getJustOneField() {
		return justOneField;
	}
	// wrong setter - won't work (needs ONLY one parameter in order to work)
	void setJustOneField() {
		justOneField = 999;
	}

	void doSomethingSimple();
};
};

#endif
