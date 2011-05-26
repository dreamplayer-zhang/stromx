#include "ThreadTest.h"

#include "TestOperator.h"

#include <DataContainer.h>
#include <OperatorWrapper.h>
#include <OperatorNode.h>
#include <None.h>
#include <InputNode.h>
#include <Thread.h>
#include <Exception.h>

#include <cppunit/TestAssert.h>
#include <boost/thread/thread.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION (stream::ThreadTest);

namespace stream
{
    void ThreadTest::setUp()
    {
        for(unsigned int i = 0; i < 3; ++i)
        {
            m_operators.push_back(new TestOperator(0));
            m_operatorWrappers.push_back(new OperatorWrapper(m_operators.back()));
            m_operatorNodes.push_back(new OperatorNode(m_operatorWrappers.back()));
        }
        
        for(unsigned int i = 0; i < 2; ++i)
        {
            m_operatorNodes[i + 1]->getInputNode(TestOperator::INPUT_1)
                ->connect(m_operatorNodes[i]->getOutputNode(TestOperator::OUTPUT_1));
                
            m_operatorNodes[i + 1]->getInputNode(TestOperator::INPUT_2)
                ->connect(m_operatorNodes[i]->getOutputNode(TestOperator::OUTPUT_2));
        }
        
        m_thread = new Thread(m_operatorNodes);
        m_container = new DataContainer(new stream::None);
    }
    
    void ThreadTest::testStart()
    {
        CPPUNIT_ASSERT_NO_THROW(m_thread->start());
        CPPUNIT_ASSERT_THROW(m_thread->start(), InvalidStateException);
        
        m_operatorWrappers[0]->setInputData(TestOperator::INPUT_1, m_container);
        m_operatorWrappers[0]->setInputData(TestOperator::INPUT_2, m_container);
        
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        
        DataContainer* data = m_operatorWrappers[2]->getOutputData(TestOperator::OUTPUT_1);
        CPPUNIT_ASSERT_EQUAL(m_container, data);
        
        data = m_operatorWrappers[2]->getOutputData(TestOperator::OUTPUT_2);
        CPPUNIT_ASSERT_EQUAL(m_container, data);
        
        for(std::vector<TestOperator*>::const_iterator iter = m_operators.begin();
            iter != m_operators.end();
            ++iter)
        {
            CPPUNIT_ASSERT_EQUAL((unsigned int)(1), (*iter)->numExecutes());
        }     
    }

    void ThreadTest::testStop()
    {
        CPPUNIT_ASSERT_NO_THROW(m_thread->stop());
        
        m_thread->start();
        CPPUNIT_ASSERT_NO_THROW(m_thread->stop());
        CPPUNIT_ASSERT_NO_THROW(m_thread->stop());
    }

    void ThreadTest::testJoin()
    {
        CPPUNIT_ASSERT_NO_THROW(m_thread->join());
        
        m_thread->start();
        m_thread->stop();
        
        CPPUNIT_ASSERT_NO_THROW(m_thread->join());
        CPPUNIT_ASSERT_NO_THROW(m_thread->join());
    }

    void ThreadTest::tearDown()
    {
        m_thread->stop();
        m_thread->join();
        
        delete m_thread;
        
        for(std::vector<OperatorWrapper*>::iterator iter = m_operatorWrappers.begin();
            iter != m_operatorWrappers.end();
            ++iter)
        {
            delete *iter;
        }
        
        for(std::vector<OperatorNode*>::iterator iter = m_operatorNodes.begin();
            iter != m_operatorNodes.end();
            ++iter)
        {
            delete *iter;
        }
        
    }
}
