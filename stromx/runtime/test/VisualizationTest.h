/* 
 *  Copyright 2015 Matthias Fuchs
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef STROMX_RUNTIME_VISUALIZATIONTEST_H
#define STROMX_RUNTIME_VISUALIZATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

namespace stromx
{
    namespace runtime
    {
        class VisualizationTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (VisualizationTest);
            CPPUNIT_TEST (testPointIsPoint);
            CPPUNIT_TEST (testPointIsData);
            CPPUNIT_TEST (testPointIsMatrix);
            CPPUNIT_TEST (testPointIsLine);
            CPPUNIT_TEST (testDataIsHistogram);
            CPPUNIT_TEST (testMatrixIsLine);
            CPPUNIT_TEST_SUITE_END ();

        public:
                void setUp() {}
                void tearDown() {}

            protected:
                void testPointIsPoint();
                void testPointIsData();
                void testPointIsMatrix();
                void testPointIsLine();
                void testDataIsHistogram();
                void testMatrixIsLine();
        };
    }
}

#endif // STROMX_RUNTIME_VISUALIZATIONTEST_H