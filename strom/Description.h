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

#ifndef STROM_DESCRIPTOR_H
#define STROM_DESCRIPTOR_H

#include <string>
#include "DataVariant.h"

namespace strom
{
    class Description
    {
    public:
        Description(const unsigned int id, const DataVariant& type)
          : m_id(id),
            m_type(type)
        {}
        
        virtual ~Description() {}
        
        const std::string & name() const { return m_name; }
        const unsigned int id() const { return m_id; }
        const DataVariant & type() const { return m_type; }
        
        void setName(const std::string & name) { m_name = name; }
        
    private:
        std::string m_name;
        unsigned int m_id;
        DataVariant m_type;
    };
}

#endif // STROM_DESCRIPTOR_H