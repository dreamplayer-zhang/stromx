#ifndef STROMX_IMGPROC_BILATERALFILTERTEST_H
#define STROMX_IMGPROC_BILATERALFILTERTEST_H

#include "stromx/imgproc/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace imgproc
    {
        class BilateralFilterTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(BilateralFilterTest);
            CPPUNIT_TEST(testManual0);
            CPPUNIT_TEST(testAllocate0);
            CPPUNIT_TEST(testAllocate1);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            BilateralFilterTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testManual0();
            void testAllocate0();
            void testAllocate1();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    }
}

#endif // STROMX_IMGPROC_BILATERALFILTERTEST_H
