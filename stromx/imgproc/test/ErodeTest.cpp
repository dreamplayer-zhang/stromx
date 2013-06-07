#include "stromx/imgproc/test/ErodeTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/imgutil/Image.h"
#include "stromx/imgproc/Erode.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::imgproc::ErodeTest);

namespace stromx
{
    namespace imgproc
    {
        void ErodeTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Erode);
        }
        
        void ErodeTest::tearDown()
        {
            delete m_operator;
        }
        
        void ErodeTest::testManual0()
        {
            m_operator->setParameter(Erode::DATA_FLOW, runtime::Enum(Erode::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            runtime::UInt32 ksizex(3);
            runtime::UInt32 ksizey(4);
            runtime::Enum shape(1);
            runtime::UInt32 iterations(2);
            
            m_operator->setInputData(Erode::SRC, src);
            m_operator->setInputData(Erode::DST, dst);
            m_operator->setParameter(Erode::KSIZEX, ksizex);
            m_operator->setParameter(Erode::KSIZEY, ksizey);
            m_operator->setParameter(Erode::SHAPE, shape);
            m_operator->setParameter(Erode::ITERATIONS, iterations);
            
            runtime::DataContainer result = m_operator->getOutputData(Erode::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ErodeTest_testManual0.png", access());
        }
        
        void ErodeTest::testManual1()
        {
            m_operator->setParameter(Erode::DATA_FLOW, runtime::Enum(Erode::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::DataContainer dst(new imgutil::Image(1000000));
            
            m_operator->setInputData(Erode::SRC, src);
            m_operator->setInputData(Erode::DST, dst);
            
            runtime::DataContainer result = m_operator->getOutputData(Erode::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ErodeTest_testManual1.png", access());
        }
        
        void ErodeTest::testAllocate0()
        {
            m_operator->setParameter(Erode::DATA_FLOW, runtime::Enum(Erode::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg"));
            
            m_operator->setInputData(Erode::SRC, src);
            
            runtime::DataContainer result = m_operator->getOutputData(Erode::DST);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ErodeTest_testAllocate0.png", access());
        }
        
        void ErodeTest::testInPlace0()
        {
            m_operator->setParameter(Erode::DATA_FLOW, runtime::Enum(Erode::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new imgutil::Image("lenna.jpg", imgutil::Image::GRAYSCALE));
            runtime::Enum shape(2);
            
            m_operator->setInputData(Erode::SRC, src);
            m_operator->setParameter(Erode::SHAPE, shape);
            
            runtime::DataContainer result = m_operator->getOutputData(Erode::SRC);
            
            runtime::ReadAccess<runtime::Image> access(result);
            imgutil::Image::save("ErodeTest_testInPlace0.png", access());
        }
        
    }
}

