#include "PeriodicDelayTest.h"

#include <base/PeriodicDelay.h>
#include <base/Image.h>

#include <strom/OperatorTester.h>
#include <strom/Exception.h>
#include <strom/ReadAccess.h>

#include <boost/thread.hpp>

#include <cppunit/TestAssert.h>

CPPUNIT_TEST_SUITE_REGISTRATION (base::PeriodicDelayTest);

using namespace strom;

namespace base
{
    void PeriodicDelayTest::setUp ( void )
    {
        m_operator = new strom::OperatorTester(new PeriodicDelay());
        m_operator->initialize();
        m_operator->activate();
        m_image = DataContainer(new Image("lenna.jpg"));
        m_operator->setInputData(PeriodicDelay::INPUT, m_image);
    }
    
    void PeriodicDelayTest::testExecute()
    {
        m_operator->setParameter(PeriodicDelay::PERIOD, strom::UInt32(1000));
        
        {
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
            ReadAccess<Image> access(result);
            const Image& image = access();
        }
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }

        m_operator->clearOutputData(PeriodicDelay::OUTPUT);
        m_operator->setInputData(PeriodicDelay::INPUT, m_image);
        boost::thread t1(boost::bind(&PeriodicDelayTest::getOutputDataInterrupted, this));
        t1.interrupt();
        t1.join();
    }
    
    void PeriodicDelayTest::testExecuteZeroPeriod()
    {
        m_operator->setParameter(PeriodicDelay::PERIOD, strom::UInt32(0));
        
        {
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
            ReadAccess<Image> access(result);
            const Image& image = access();
        }
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }   
        
        {
            m_operator->clearOutputData(PeriodicDelay::OUTPUT);
            m_operator->setInputData(PeriodicDelay::INPUT, m_image);
            DataContainer result = m_operator->getOutputData(PeriodicDelay::PERIOD);
        }
    }
    
    void PeriodicDelayTest::getOutputDataInterrupted()
    {
        CPPUNIT_ASSERT_THROW(m_operator->getOutputData(PeriodicDelay::OUTPUT), Interrupt);
    }
    
    void PeriodicDelayTest::tearDown ( void )
    {
        delete m_operator;
    }
}