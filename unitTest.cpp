#include "unitTest.h"
#include "LoginAccess.h"


CPPUNIT_TEST_SUITE_REGISTRATION(unitTest);

unitTest::unitTest() {
}

unitTest::~unitTest() {
}

void unitTest::setUp() {
}

void unitTest::tearDown() {
}

bool checkPassword(string pass);

void unitTest::testCheckPassword() {
    string str = "abcdefgh";
    cout << "\nChecking if " << str << " return false\n";
    bool result = checkPassword(str);
    CPPUNIT_ASSERT_MESSAGE("Should be false", result == false);

    str = "abcdefgh1";
    cout << "\nChecking if " << str << " return true\n";
    result = checkPassword(str);
    CPPUNIT_ASSERT_MESSAGE("Should be true", result == true);

}

void unitTest::testLoginAccess() {
    LoginAccess l;
    cout << "\nChecking if loginTries is set to 0" << endl;
    CPPUNIT_ASSERT_MESSAGE("Login Tries should be defaulted to 0",
                            l.getLoginTries() == 0);
    
    cout << "Checking if cashierIndex is set to 0" << endl;
    CPPUNIT_ASSERT_MESSAGE("CashierIndex should be defaulted to 0",
                            l.getCashierIndex() == 0);

    cout << "Checking if cashier extracted is bigger than 0 " << endl;
    CPPUNIT_ASSERT_MESSAGE("No cashier extracted", l.getCashierSize() > 0);
}


