#ifndef STROMX_CVOBJDETECT_CASCADECLASSIFIER_H
#define STROMX_CVOBJDETECT_CASCADECLASSIFIER_H

#include "stromx/cvobjdetect/Config.h"
#include <stromx/cvsupport/Matrix.h>
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/List.h>
#include <stromx/runtime/MatrixDescription.h>
#include <stromx/runtime/MatrixParameter.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/Primitive.h>

namespace stromx
{
    namespace cvobjdetect
    {
        class STROMX_CVOBJDETECT_API CascadeClassifier : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                ALLOCATE
            };
            enum ConnectorId
            {
                SRC,
                DST
            };
            enum ParameterId
            {
                DATA_FLOW
            };
            CascadeClassifier();
            virtual OperatorKernel* clone() const { return new CascadeClassifier; }
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
            
            runtime::Enum m_dataFlow;
            runtime::Description* m_dstDescription;
            runtime::Description* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvobjdetect
} // stromx

#endif // STROMX_CVOBJDETECT_CASCADECLASSIFIER_H
