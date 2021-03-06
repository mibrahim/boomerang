#include "util.h"
#include "type.h"

#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

class UtilTest : public CppUnit::TestCase {
protected:

public:
	UtilTest(std::string name) : CppUnit::TestCase(name)
	{}

	virtual void registerTests(CppUnit::TestSuite *suite);

	int countTestCases() const;

	void setUp();
	void tearDown();

	void testTypeLong();
	void testNotEqual();
};
