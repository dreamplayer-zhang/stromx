#include "stromx/imgproc/MedianBlur.h"

#include "stromx/imgproc/Utility.h"
#include <stromx/imgutil/Image.h>
#include <stromx/imgutil/Matrix.h>
#include <stromx/imgutil/Utilities.h>
#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/Id2DataComposite.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/WriteAccess.h>
#include <opencv2/imgproc/imgproc.hpp>

namespace stromx
{
    namespace imgproc
    {
        const std::string MedianBlur::PACKAGE(STROMX_IMGPROC_PACKAGE_NAME);
        const runtime::Version MedianBlur::VERSION(STROMX_IMGPROC_VERSION_MAJOR, STROMX_IMGPROC_VERSION_MINOR, STROMX_IMGPROC_VERSION_PATCH);
        const std::string MedianBlur::TYPE("MedianBlur");
        
        MedianBlur::MedianBlur()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_ksize(3),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef MedianBlur::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case KSIZE:
                return m_ksize;
            case DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void MedianBlur::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case KSIZE:
                    {
                        runtime::UInt32 castedValue = runtime::data_cast<runtime::UInt32>(value);
                        checkNumericValue(castedValue, m_ksizeParameter, *this);
                        if(int(castedValue) % 2 == 0)
                            throw runtime::WrongParameterValue(*m_ksizeParameter, *this, "Only odd values are allowed");
                        m_ksize = castedValue;
                    }
                    break;
                case DATA_FLOW:
                    {
                        runtime::Enum castedValue = runtime::data_cast<runtime::Enum>(value);
                        checkEnumValue(castedValue, m_dataFlowParameter, *this);
                        m_dataFlow = castedValue;
                    }
                    break;
                default:
                    throw runtime::WrongParameterId(id, *this);
                }
            }
            catch(runtime::BadCast&)
            {
                throw runtime::WrongParameterType(parameter(id), *this);
            }
        }
        
        const std::vector<const runtime::Parameter*> MedianBlur::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            m_dataFlowParameter = new runtime::EnumParameter(DATA_FLOW);
            m_dataFlowParameter->setAccessMode(runtime::Parameter::NONE_WRITE);
            m_dataFlowParameter->setTitle("Data flow");
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(MANUAL), "Manual"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(ALLOCATE), "Allocate"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(IN_PLACE), "In place"));
            parameters.push_back(m_dataFlowParameter);
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> MedianBlur::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_ksizeParameter = new runtime::NumericParameter<runtime::UInt32>(KSIZE);
                    m_ksizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeParameter->setTitle("Kernel size");
                    m_ksizeParameter->setMin(runtime::UInt32(1));
                    m_ksizeParameter->setStep(runtime::UInt32(2));
                    parameters.push_back(m_ksizeParameter);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_ksizeParameter = new runtime::NumericParameter<runtime::UInt32>(KSIZE);
                    m_ksizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeParameter->setTitle("Kernel size");
                    m_ksizeParameter->setMin(runtime::UInt32(1));
                    m_ksizeParameter->setStep(runtime::UInt32(2));
                    parameters.push_back(m_ksizeParameter);
                    
                }
                break;
            case(IN_PLACE):
                {
                    m_ksizeParameter = new runtime::NumericParameter<runtime::UInt32>(KSIZE);
                    m_ksizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeParameter->setTitle("Kernel size");
                    m_ksizeParameter->setMin(runtime::UInt32(1));
                    m_ksizeParameter->setStep(runtime::UInt32(2));
                    parameters.push_back(m_ksizeParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Description*> MedianBlur::setupInputs()
        {
            std::vector<const runtime::Description*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Description* src = new runtime::Description(SRC, runtime::DataVariant::IMAGE);
                    src->setTitle("Source");
                    inputs.push_back(src);
                    
                    runtime::Description* dst = new runtime::Description(DST, runtime::DataVariant::IMAGE);
                    dst->setTitle("Destination");
                    inputs.push_back(dst);
                    
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Description* src = new runtime::Description(SRC, runtime::DataVariant::IMAGE);
                    src->setTitle("Source");
                    inputs.push_back(src);
                    
                }
                break;
            case(IN_PLACE):
                {
                    runtime::Description* src = new runtime::Description(SRC, runtime::DataVariant::IMAGE);
                    src->setTitle("Source");
                    inputs.push_back(src);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Description*> MedianBlur::setupOutputs()
        {
            std::vector<const runtime::Description*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Description* dst = new runtime::Description(DST, runtime::DataVariant::IMAGE);
                    dst->setTitle("Destination");
                    outputs.push_back(dst);
                    
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Description* dst = new runtime::Description(DST, runtime::DataVariant::IMAGE);
                    dst->setTitle("Destination");
                    outputs.push_back(dst);
                    
                }
                break;
            case(IN_PLACE):
                {
                    runtime::Description* src = new runtime::Description(SRC, runtime::DataVariant::IMAGE);
                    src->setTitle("Source");
                    outputs.push_back(src);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void MedianBlur::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void MedianBlur::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Id2DataPair srcInMapper(SRC);
                    runtime::Id2DataPair dstInMapper(DST);
                    
                    provider.receiveInputData(srcInMapper && dstInMapper);
                    
                    const runtime::Data* srcData = 0;
                    runtime::Data* dstData = 0;
                    
                    runtime::ReadAccess<> srcReadAccess;
                    runtime::DataContainer inContainer = dstInMapper.data();
                    runtime::WriteAccess<> writeAccess(inContainer);
                    dstData = &writeAccess();
                    
                    if(srcInMapper.data() == inContainer)
                    {
                        srcData = &writeAccess();
                    }
                    else
                    {
                        srcReadAccess = runtime::ReadAccess<>(srcInMapper.data());
                        srcData = &srcReadAccess();
                    }
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    runtime::Image * dstCastedData = runtime::data_cast<runtime::Image>(dstData);
                    
                    dstCastedData->initializeImage(srcCastedData->width(), srcCastedData->height(), srcCastedData->stride(), dstCastedData->data(), srcCastedData->pixelType());
                    
                    cv::Mat srcCvData = imgutil::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData = imgutil::getOpenCvMat(*dstCastedData);
                    int ksizeCvData = int(m_ksize);
                    
                    cv::medianBlur(srcCvData, dstCvData, ksizeCvData);
                    
                    runtime::DataContainer outContainer = inContainer;
                    runtime::Id2DataPair outputMapper(DST, outContainer);
                    
                    provider.sendOutputData(outputMapper);
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Id2DataPair srcInMapper(SRC);
                    
                    provider.receiveInputData(srcInMapper);
                    
                    const runtime::Data* srcData = 0;
                    
                    runtime::ReadAccess<> srcReadAccess;
                    
                    srcReadAccess = runtime::ReadAccess<>(srcInMapper.data());
                    srcData = &srcReadAccess();
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    
                    cv::Mat srcCvData = imgutil::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData;
                    int ksizeCvData = int(m_ksize);
                    
                    cv::medianBlur(srcCvData, dstCvData, ksizeCvData);
                    
                    runtime::Image* dstCastedData = new imgutil::Image(dstCvData);
                    runtime::DataContainer outContainer = runtime::DataContainer(dstCastedData);
                    runtime::Id2DataPair outputMapper(DST, outContainer);
                    
                    dstCastedData->initializeImage(dstCastedData->width(), dstCastedData->height(), dstCastedData->stride(), dstCastedData->data(), srcCastedData->pixelType());
                    provider.sendOutputData(outputMapper);
                }
                break;
            case(IN_PLACE):
                {
                    runtime::Id2DataPair srcInMapper(SRC);
                    
                    provider.receiveInputData(srcInMapper);
                    
                    runtime::Data* srcData = 0;
                    
                    runtime::DataContainer inContainer = srcInMapper.data();
                    runtime::WriteAccess<> writeAccess(inContainer);
                    srcData = &writeAccess();
                    
                    runtime::Image * srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    
                    cv::Mat srcCvData = imgutil::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData = srcCvData;
                    int ksizeCvData = int(m_ksize);
                    
                    cv::medianBlur(srcCvData, dstCvData, ksizeCvData);
                    
                    runtime::DataContainer outContainer = inContainer;
                    runtime::Id2DataPair outputMapper(SRC, outContainer);
                    
                    provider.sendOutputData(outputMapper);
                }
                break;
            }
        }
        
    }
}

