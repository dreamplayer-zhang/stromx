#ifndef STROMX_CVCORE_BITWISE_XORTEST_H
#define STROMX_CVCORE_BITWISE_XORTEST_H

#include "stromx/cvcore/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace cvcore
    {
        class Bitwise_xorTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(Bitwise_xorTest);
            CPPUNIT_TEST(testManual0);
            CPPUNIT_TEST(testManual1);
            CPPUNIT_TEST(testAllocate0);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            Bitwise_xorTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testManual0();
            void testManual1();
            void testAllocate0();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    }
}

#endif // STROMX_CVCORE_BITWISE_XORTEST_H