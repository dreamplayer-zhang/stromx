#ifndef STROMX_CVIMGPROC_BOUNDINGRECTTEST_H
#define STROMX_CVIMGPROC_BOUNDINGRECTTEST_H

#include "stromx/cvimgproc/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace cvimgproc
    {
        class BoundingRectTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(BoundingRectTest);
            CPPUNIT_TEST(testAllocate0);
            CPPUNIT_TEST(testAllocate1);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            BoundingRectTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testAllocate0();
            void testAllocate1();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    }
}

#endif // STROMX_CVIMGPROC_BOUNDINGRECTTEST_H
