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

typedef enum {
	kValue100
} someEnum2;

struct someStruct1 {
	CCNode* n;

	void test(const int& f);
};

typedef struct {
	int i;
	float f;
	double d;
	CCNode* n;

	void test(const int& f);
} someStruct2;

typedef int* SEL_Custom;

class CC_DLL SimpleNativeClass : public CCNode
{
public:
	enum someClassEnum {
		kValue5,
		kValue6
	};

	enum someClassEnum2 {
		kValue7,
		kValue8
	};

	typedef struct {
		CCLayer* t;
	} someStruct4;

	typedef enum {
		kValue101
	} someEnum3;

public:
	struct someStruct3 {
		CCNode* n;

		void test(const int& f);
	};

protected:
	int m_someField;
	char* m_anotherMoreComplexField;

public:
	CCNode* m_owner;
	CREATE_FUNC(SimpleNativeClass)
    static const uint32_t OBJECT_TYPE = 0x777;
    int m_someOtherField;
    virtual uint32_t getObjectType() {
        return SimpleNativeClass::OBJECT_TYPE;
    };

    SimpleNativeClass();
	SimpleNativeClass(int m) : m_someField(m) {};
	SimpleNativeClass(int m1, int m2 = 3) : m_someField(m1), m_someOtherField(m2) {};
	virtual ~SimpleNativeClass();
	virtual bool init();

	// these methods are simple, can be defined inline
	int processGLubyte(GLubyte b);
	int processSEL_CallFunc(SEL_Custom c);
	int processSomeStruct1(someStruct1 s);
	int processSomeStruct2(someStruct2 s);
	int processSomeStruct3(someStruct3 s);
	int processSomeStruct4(someStruct4* s);
	int processSomeEnum2(someEnum2 e);
	int processSomeEnum3(someEnum3 e);
	int processClassEnum(someClassEnum e);
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
	void setSomeField(const CCNode& n, CCNode* pn) {

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
