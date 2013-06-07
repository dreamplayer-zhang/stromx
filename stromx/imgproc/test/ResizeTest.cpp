#include "stromx/imgproc/test/ResizeTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/imgutil/Image.h"
#include "stromx/imgproc/Resize.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::imgproc::ResizeTest);

namespace stromx
{
    namespace imgproc
    {
        void ResizeTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Resize);
        }
        
        void ResizeTest::tearDown()
        {
            delete m_operator;
        }
        
        void ResizeTest::testManual0()
        {
            m_operator->setParameter(Resize::DATA_FLOW, runtime::Enum(Resize::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            
            m_operator->setInputData(Resize::SRC, src);
            m_operator->setInputData(Resize::DST, dst);
            
            runtime::DataContainer result = m_operator->getOutputData(Resize::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ResizeTest_testManual0.png", access());
        }
        
        void ResizeTest::testManual1()
        {
            m_operator->setParameter(Resize::DATA_FLOW, runtime::Enum(Resize::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            runtime::UInt32 dsizex(100);
            runtime::UInt32 dsizey(200);
            runtime::Double fx(0);
            
            m_operator->setInputData(Resize::SRC, src);
            m_operator->setInputData(Resize::DST, dst);
            m_operator->setParameter(Resize::DSIZEX, dsizex);
            m_operator->setParameter(Resize::DSIZEY, dsizey);
            m_operator->setParameter(Resize::FX, fx);
            
            runtime::DataContainer result = m_operator->getOutputData(Resize::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ResizeTest_testManual1.png", access());
        }
        
        void ResizeTest::testManual2()
        {
            m_operator->setParameter(Resize::DATA_FLOW, runtime::Enum(Resize::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            runtime::UInt32 dsizex(100);
            runtime::UInt32 dsizey(200);
            runtime::Double fx(0.5);
            runtime::Double fy(0.3);
            
            m_operator->setInputData(Resize::SRC, src);
            m_operator->setInputData(Resize::DST, dst);
            m_operator->setParameter(Resize::DSIZEX, dsizex);
            m_operator->setParameter(Resize::DSIZEY, dsizey);
            m_operator->setParameter(Resize::FX, fx);
            m_operator->setParameter(Resize::FY, fy);
            
            runtime::DataContainer result = m_operator->getOutputData(Resize::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ResizeTest_testManual2.png", access());
        }
        
        void ResizeTest::testAllocate0()
        {
            m_operator->setParameter(Resize::DATA_FLOW, runtime::Enum(Resize::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::Double fx(0.5);
            runtime::Double fy(0.3);
            
            m_operator->setInputData(Resize::SRC, src);
            m_operator->setParameter(Resize::FX, fx);
            m_operator->setParameter(Resize::FY, fy);
            
            runtime::DataContainer result = m_operator->getOutputData(Resize::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ResizeTest_testAllocate0.png", access());
        }
        
    }
}

