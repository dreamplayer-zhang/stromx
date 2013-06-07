#include "stromx/imgproc/test/ScharrTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/imgutil/Image.h"
#include "stromx/imgproc/Scharr.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::imgproc::ScharrTest);

namespace stromx
{
    namespace imgproc
    {
        void ScharrTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Scharr);
        }
        
        void ScharrTest::tearDown()
        {
            delete m_operator;
        }
        
        void ScharrTest::testManual0()
        {
            m_operator->setParameter(Scharr::DATA_FLOW, runtime::Enum(Scharr::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            runtime::Enum ddepth(0);
            runtime::UInt32 dx(0);
            runtime::UInt32 dy(1);
            runtime::Double scale(1);
            runtime::Double delta(0);
            
            m_operator->setInputData(Scharr::SRC, src);
            m_operator->setInputData(Scharr::DST, dst);
            m_operator->setParameter(Scharr::DDEPTH, ddepth);
            m_operator->setParameter(Scharr::DX, dx);
            m_operator->setParameter(Scharr::DY, dy);
            m_operator->setParameter(Scharr::SCALE, scale);
            m_operator->setParameter(Scharr::DELTA, delta);
            
            runtime::DataContainer result = m_operator->getOutputData(Scharr::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ScharrTest_testManual0.png", access());
        }
        
        void ScharrTest::testManual1()
        {
            m_operator->setParameter(Scharr::DATA_FLOW, runtime::Enum(Scharr::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            runtime::Enum ddepth(1);
            runtime::UInt32 dx(1);
            runtime::UInt32 dy(0);
            runtime::Double scale(1);
            runtime::Double delta(0);
            
            m_operator->setInputData(Scharr::SRC, src);
            m_operator->setInputData(Scharr::DST, dst);
            m_operator->setParameter(Scharr::DDEPTH, ddepth);
            m_operator->setParameter(Scharr::DX, dx);
            m_operator->setParameter(Scharr::DY, dy);
            m_operator->setParameter(Scharr::SCALE, scale);
            m_operator->setParameter(Scharr::DELTA, delta);
            
            runtime::DataContainer result = m_operator->getOutputData(Scharr::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ScharrTest_testManual1.png", access());
        }
        
        void ScharrTest::testAllocate0()
        {
            m_operator->setParameter(Scharr::DATA_FLOW, runtime::Enum(Scharr::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            runtime::Enum ddepth(0);
            runtime::Double scale(2);
            
            m_operator->setInputData(Scharr::SRC, src);
            m_operator->setParameter(Scharr::DDEPTH, ddepth);
            m_operator->setParameter(Scharr::SCALE, scale);
            
            runtime::DataContainer result = m_operator->getOutputData(Scharr::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ScharrTest_testAllocate0.png", access());
        }
        
        void ScharrTest::testAllocate1()
        {
            m_operator->setParameter(Scharr::DATA_FLOW, runtime::Enum(Scharr::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::Enum ddepth(2);
            runtime::UInt32 dx(0);
            runtime::UInt32 dy(1);
            runtime::Double scale(100);
            
            m_operator->setInputData(Scharr::SRC, src);
            m_operator->setParameter(Scharr::DDEPTH, ddepth);
            m_operator->setParameter(Scharr::DX, dx);
            m_operator->setParameter(Scharr::DY, dy);
            m_operator->setParameter(Scharr::SCALE, scale);
            
            runtime::DataContainer result = m_operator->getOutputData(Scharr::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ScharrTest_testAllocate1.png", access());
        }
        
    }
}

