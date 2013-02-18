#ifndef UNITTEST_H
#define	UNITTEST_H

#include <cppunit/extensions/HelperMacros.h>

class unitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(unitTest);

    CPPUNIT_TEST(testCheckPassword);
    CPPUNIT_TEST(testLoginAccess);

    CPPUNIT_TEST_SUITE_END();

public:
    unitTest();
    virtual ~unitTest();
    void setUp();
    void tearDown();

private:
    void testCheckPassword();
    void testLoginAccess();
};

#endif	/* UNITTEST_H */

