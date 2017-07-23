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

#include <stromx/runtime/Registry.h>
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/Data.h>

#include <boost/python.hpp>

using namespace boost::python;
using namespace stromx::runtime;

namespace
{
    struct RegistryWrap : Registry, wrapper<Registry>
    {
        void registerOperator(const OperatorKernel* const op)
        {
            this->get_override("registerOperator")(op);
        }
        
        void registerData(const Data* data)
        {
            this->get_override("registerData")(data);
        }
    };
        
    intptr_t _this(Registry& registry)
    {
        return reinterpret_cast<intptr_t>(&registry);
    }
}

void exportRegistry()
{          
    class_<RegistryWrap, boost::noncopyable>("Registry", no_init)
        .def("registerOperator", pure_virtual(&Registry::registerOperator))
        .def("registerData", pure_virtual(&Registry::registerData))
        .def("_this", &_this)
    ;
}
