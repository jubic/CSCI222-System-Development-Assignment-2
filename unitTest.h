#ifndef UNITTEST_H
#define UNITTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "main.h"
class unitTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(unitTest);
	CPPUNIT_TEST(testString);
	CPPUNIT_TEST(testWarning);
	CPPUNIT_TEST(testWarning2);
	CPPUNIT_TEST(testWarning3);
	CPPUNIT_TEST_SUITE_END();

public:
    unitTest();
    virtual ~unitTest();
private:
	void testString();
	void testWarning();
	void testWarning2();
	void testWarning3();
};

#endif	/* UNITTEST_H */

