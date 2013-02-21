#include "unitTest.h"
CPPUNIT_TEST_SUITE_REGISTRATION(unitTest);

unitTest::unitTest() {
}

unitTest::~unitTest() {
}

void unitTest::testString() {
	Function tempFunc;
	
	string str1="1234567a";
	const int NUMBER = 100;
	char char1[NUMBER];

	strcpy(char1,str1.c_str());
	int nx = strlen(char1);
	int te = tempFunc.testStr(char1, nx);

	cout << "\nChecking if " << str1 << " return true\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true",te==1);

	string str2="1234567";
	char char2[NUMBER];
	strcpy(char2,str2.c_str());
	nx = strlen(char2);

	cout << "\nChecking if " << str2 << " return false\n";
	CPPUNIT_ASSERT_MESSAGE("Should be false",nx<8);

	string str3="1234567";
	char char3[NUMBER];
	strcpy(char3,str3.c_str());
	nx = strlen(char3);
	te = tempFunc.testStr(char1, nx);

	cout << "\nChecking if " << str3 << " return true\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true",te==2);

	string str4="abcdefgh";
	char char4[NUMBER];
	strcpy(char4,str4.c_str());
	nx = strlen(char4);
	te = tempFunc.testStr(char4, nx);

	cout << "\nChecking if " << str4 << " return true\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true",te==3);
}

void unitTest::testWarning() {
	mFunction mTempFunc;
	int check = mTempFunc.check_warning("S8906543U", "CSCI212");
	cout << "\nChecking if check return 1\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true", check==1);
}
void unitTest::testWarning2() {
	mFunction mTempFunc;
	int check = mTempFunc.check_warning("S7632334E", "CSCI212");
	cout << "\nChecking if check return 0\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true", check==0);
}
void unitTest::testWarning3() {
	mFunction mTempFunc;
	int check = mTempFunc.check_warning("S9028374U", "CSCI222");
	cout << "\nChecking if check return 3\n";
	CPPUNIT_ASSERT_MESSAGE("Should be true", check==3);
}

