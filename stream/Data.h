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

#ifndef STREAM_DATA_H
#define STREAM_DATA_H

#include "DataVariant.h"

namespace stream
{
    class Version;
    
    class Data
    {
    public:
        virtual ~Data() {}
        
        virtual const Version & version() const = 0;
        virtual const std::string & name() const = 0;
        virtual const std::string & package() const = 0;
        virtual const DataVariant & variant() const = 0;
        
        virtual Data* const clone() const = 0;
        
        virtual const std::string serialize(const std::string & name, const std::string & path) const;
        virtual void deserialize(const std::string & data, const std::string & path);
        
        bool is(const DataVariant & t) const { return variant().is(t); }
        
    protected:
        Data() {} 
    };
}

#endif // STREAM_DATA_H