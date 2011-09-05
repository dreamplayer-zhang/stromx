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

#ifndef MATH_ADDANDMULTIPLY_H
#define MATH_ADDANDMULTIPLY_H

#include <stream/OperatorKernel.h>
#include <stream/Primitive.h>

namespace stream
{
    class DataContainer;
}

namespace math
{
    class AddAndMultiply : public stream::OperatorKernel
    {
    public:
        enum InputId
        {
            INPUT_1,
            INPUT_2
        };
        
        enum OutputId
        {
            OUTPUT
        };
        
        enum ParameterId
        {
            COEFFICIENT
        };
        
        AddAndMultiply();
        
        virtual OperatorKernel* const clone() const { return new AddAndMultiply; }
        virtual void setParameter(unsigned int id, const stream::Data& value);
        virtual const stream::Data& getParameter(unsigned int id);
        virtual void execute(stream::DataProvider& provider);
        
    private:
        static const std::vector<const stream::Description*> setupInputs();
        static const std::vector<const stream::Description*> setupOutputs();
        static const std::vector<const stream::Parameter*> setupParameters();
        
        static const std::string TYPE;
        static const std::string PACKAGE;
        static const stream::Version VERSION;                         
        
        stream::Double m_coefficient;
        
        const double extractDouble(const stream::DataContainer& dataContainer);
    };
}

#endif // MATH_ADDANDMULTIPLY_H
