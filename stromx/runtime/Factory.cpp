/* 
 *  Copyright 2011 Thomas Fidler
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

#include <boost/thread.hpp>
#include "stromx/runtime/Data.h"
#include "stromx/runtime/Exception.h"
#include "stromx/runtime/Factory.h"
#include "stromx/runtime/Operator.h"
#include "stromx/runtime/OperatorKernel.h"
#include "stromx/runtime/impl/MutexHandle.h"

namespace stromx
{
    namespace runtime
    {        
        Factory::Factory()
          :  m_mutex(new impl::MutexHandle())
        {}
        
        Factory::Factory(const Factory& factory)
          :  m_mutex(new impl::MutexHandle())
        {
            for(std::vector<const OperatorKernel*>::const_iterator iter = factory.m_operators.begin();
                iter != factory.m_operators.end();
                ++iter)
            {
                m_operators.push_back((*iter)->clone());
            }
            
            for(std::vector<const Data*>::const_iterator iter = factory.m_dataTypes.begin();
                iter != factory.m_dataTypes.end();
                ++iter)
            {
                m_dataTypes.push_back((*iter)->clone());
            }
        }

        Factory::~Factory()
        {
            for(std::vector<const OperatorKernel*>::iterator iter = m_operators.begin();
                iter != m_operators.end();
                ++iter)
            {
                delete (*iter);
            }
            
            for(std::vector<const Data*>::iterator iter = m_dataTypes.begin();
                iter != m_dataTypes.end();
                ++iter)
            {
                delete (*iter);
            }
            
            delete m_mutex;
        }

        void Factory::registerOperator(const OperatorKernel*const op)
        {
            boost::lock_guard<boost::mutex> lock(m_mutex->mutex());
            
            if(op == 0)
            {
                throw WrongArgument("Invalid argument: Null pointer.");
            }
            
            for(std::vector<const OperatorKernel*>::iterator iter = m_operators.begin();
                iter != m_operators.end();
                ++iter)
            {
                if(op->type() == (*iter)->type() && op->package() == (*iter)->package())
                {
                    throw WrongArgument("Invalid argument: Operator (" 
                        + op->package() + ", " + op->type() 
                        + ") has already been registered.");
                }
            }
            
            m_operators.push_back(op);
        }

        void Factory::registerData(const Data* data)
        {
            boost::lock_guard<boost::mutex> lock(m_mutex->mutex());
            
            if(data == 0)
            {
                throw WrongArgument("Invalid argument: Null pointer.");
            }
            
            for(std::vector<const Data*>::iterator iter = m_dataTypes.begin();
                iter != m_dataTypes.end();
                ++iter)
            {
                if(data->type() == (*iter)->type() && data->package() == (*iter)->package())
                {
                    throw WrongArgument("Invalid argument: Data (" 
                        + data->package() + ", " + data->type() 
                        + ") has already been registered.");
                }
            }
            
            m_dataTypes.push_back(data);
        }

        OperatorKernel* Factory::newOperator(const std::string& package, const std::string& type) const
        {
            boost::lock_guard<boost::mutex> lock(m_mutex->mutex());
            
            for(std::vector<const OperatorKernel*>::const_iterator iter = m_operators.begin();
                iter != m_operators.end();
                ++iter)
            {
                if((*iter)->type() == type && (*iter)->package() == package)
                {
                    OperatorKernel* newOpKernel = 0;
                    newOpKernel = (*iter)->clone();
                    if (newOpKernel == 0)
                    { 
                        throw InternalError("Invalid argument received: Null pointer. Cloning failed");
                    }

                    return newOpKernel;
                }
            }
            
            throw OperatorAllocationFailed(package, type, "Invalid argument: Operator (" 
                + package + ", " + type + ") has not been registered.");        
        }

        Data* Factory::newData(const std::string& package, const std::string& type) const
        {
            boost::lock_guard<boost::mutex> lock(m_mutex->mutex());
            
            for(std::vector<const Data*>::const_iterator iter = m_dataTypes.begin();
                iter != m_dataTypes.end();
                ++iter)
            {
                if((*iter)->type() == type && (*iter)->package() == package)
                {
                    Data* newData = 0;
                    newData = (*iter)->clone();
                    if (newData == 0)
                    { 
                        throw InternalError("Invalid argument: Null pointer. Cloning failed");
                    }

                    return newData;
                }
            }
            
            throw DataAllocationFailed(package, type, "Invalid argument: Data (" 
                + package + ", " + type + ") has not been registered.");        
        }
    } 
}
