/* 
 *  Copyright 2011 Matthias Fuchs
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

#ifndef STROMX_RUNTIME_OUTPUTNODETEST_H
#define STROMX_RUNTIME_OUTPUTNODETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "stromx/runtime/DataContainer.h"

namespace stromx
{
    namespace runtime
    {
        class Operator;
        
        namespace impl
        {
            class OutputNode;
            class InputNode;
        }
        
        class OutputNodeTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (OutputNodeTest);
            CPPUNIT_TEST(testGetOutputData);
            CPPUNIT_TEST(testAddConnectedInputs);
            CPPUNIT_TEST(testRemoveConnectedInputs);
            CPPUNIT_TEST(testTwoInputs);
            CPPUNIT_TEST(testReset);
            CPPUNIT_TEST_SUITE_END ();

        public:
            OutputNodeTest() : m_operatorWrapper(0), m_outputNode(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void testGetOutputData();
            void testAddConnectedInputs();
            void testRemoveConnectedInputs();
            void testTwoInputs();
            void testReset();
                
        private: 
            Operator* m_operatorWrapper;
            DataContainer m_container;
            impl::OutputNode* m_outputNode;
        };
    }
}

#endif // STROMX_RUNTIME_OUTPUTNODETEST_H