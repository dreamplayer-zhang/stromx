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

#include <cppunit/TestAssert.h>
#include "InputNodeTest.h"
#include "TestOperator.h"
#include "../DataContainer.h"
#include "../Exception.h"
#include "../None.h"
#include "../Operator.h"
#include "../impl/InputNode.h"
#include "../impl/OutputNode.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::core::InputNodeTest);

namespace stromx
{
    namespace core
    {
        using namespace impl;
        
        void InputNodeTest::setUp()
        {
            m_operatorWrapper = new Operator(new TestOperator());
            m_operatorWrapper->initialize();
            m_operatorWrapper->activate();
            m_sourceOperatorWrapper = new Operator(new TestOperator());
            m_sourceOperatorWrapper->initialize();
            m_sourceOperatorWrapper->activate();
            
            m_container = DataContainer(new core::None);
            m_inputNode = new InputNode(m_operatorWrapper, TestOperator::INPUT_1);
            m_sourceNode = new OutputNode(m_sourceOperatorWrapper, TestOperator::OUTPUT_2);
        }
        
        void InputNodeTest::testConnect()
        {
            CPPUNIT_ASSERT_NO_THROW(m_inputNode->connect(m_sourceNode));
            CPPUNIT_ASSERT_THROW(m_inputNode->connect(m_sourceNode), WrongState);
        }
        
        void InputNodeTest::testSource()
        {
            CPPUNIT_ASSERT_THROW(m_inputNode->source(), WrongState);
            
            m_inputNode->connect(m_sourceNode);
            CPPUNIT_ASSERT_EQUAL((const OutputNode*)(m_sourceNode), &(m_inputNode->source()));
        }

        void InputNodeTest::testDisconnect()
        {
            CPPUNIT_ASSERT_NO_THROW(m_inputNode->disconnect());
            
            m_inputNode->connect(m_sourceNode);
            CPPUNIT_ASSERT_NO_THROW(m_inputNode->disconnect());
            CPPUNIT_ASSERT_NO_THROW(m_inputNode->connect(m_sourceNode));
        }

        void InputNodeTest::testSetInputData()
        {
            m_inputNode->connect(m_sourceNode);
            m_sourceOperatorWrapper->setInputData(TestOperator::INPUT_1, m_container);
            m_sourceOperatorWrapper->setInputData(TestOperator::INPUT_2, m_container);
            CPPUNIT_ASSERT_NO_THROW(m_inputNode->setInputData());
        }

        void InputNodeTest::tearDown()
        {
            delete m_operatorWrapper;
            delete m_sourceOperatorWrapper;
            delete m_inputNode;
            delete m_sourceNode;
        }   
    }
}


