#ifndef STROMX_IMGPROC_ADAPTIVETHRESHOLD_H
#define STROMX_IMGPROC_ADAPTIVETHRESHOLD_H

#include "stromx/imgproc/Config.h"
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/Primitive.h>

namespace stromx
{
    namespace imgproc
    {
        class STROMX_IMGPROC_API AdaptiveThreshold : public runtime::OperatorKernel
        {
        public:
            enum AdaptiveMethodId
            {
                ADAPTIVE_THRESH_MEAN_C,
                 ADAPTIVE_THRESH_GAUSSIAN_C
            };
            enum ThresholdTypeId
            {
                THRESH_BINARY,
                THRESH_BINARY_INV,
                THRESH_TRUNC,
                THRESH_TOZERO,
                THRESH_TOZERO_INV
            };
            enum DataFlowId
            {
                MANUAL,
                ALLOCATE,
                IN_PLACE
            };
            enum ConnectorId
            {
                SRC,
                DST
            };
            enum ParameterId
            {
                ADAPTIVE_METHOD,
                THRESHOLD_TYPE,
                BLOCK_SIZE,
                DATA_FLOW,
                MAXVAL
            };
            AdaptiveThreshold();
            virtual OperatorKernel* clone() const { return new AdaptiveThreshold; }
            virtual void setParameter(const unsigned int id, const runtime::Data& value);
            virtual const runtime::DataRef getParameter(const unsigned int id) const;
            void initialize();
            virtual void execute(runtime::DataProvider& provider);
            
        private:
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            static const std::string TYPE;
            
            const std::vector<const runtime::Parameter*> setupInitParameters();
            const std::vector<const runtime::Parameter*> setupParameters();
            const std::vector<const runtime::Description*> setupInputs();
            const std::vector<const runtime::Description*> setupOutputs();
            
            int convertAdaptiveMethod(const runtime::Enum & value);
            int convertThresholdType(const runtime::Enum & value);
            
            runtime::Enum m_adaptiveMethod;
            runtime::UInt32 m_blockSize;
            runtime::Double m_maxval;
            runtime::Enum m_thresholdType;
            runtime::Enum m_dataFlow;
            runtime::EnumParameter* m_adaptiveMethodParameter;
            runtime::NumericParameter<runtime::UInt32>* m_blockSizeParameter;
            runtime::NumericParameter<runtime::Double>* m_maxvalParameter;
            runtime::EnumParameter* m_thresholdTypeParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    }
}

#endif // STROMX_IMGPROC_ADAPTIVETHRESHOLD_H