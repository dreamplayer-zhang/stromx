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

#ifndef STROM_XMLWRITERIMPL_H
#define STROM_XMLWRITERIMPL_H

#include <xercesc/dom/DOM.hpp>
#include <string>
#include "../Node.h"
#include "../Operator.h"
#include "../Parameter.h"
#include "../Stream.h"
#include "XmlUtilities.h"

namespace stromx
{
    namespace core
    {
        class Stream;
        
        namespace impl
        {
            class XmlWriterImpl
            {
            public:
                XmlWriterImpl();
                ~XmlWriterImpl() {};
                void write(const std::string & filename, const Stream& stream);
                
            private:
                const unsigned int translateOperatorPointerToID(const Operator* const op) const;
                void createThreads(const std::vector<Thread*> threads);
                void createInputNodes(const Thread* const currThr, xercesc::DOMElement* const thrElement);
                void createOperators(const std::vector<Operator*> operators);
                void createParameters(const Operator* const currOp, xercesc::DOMElement* const opElement);
                void createData(const Parameter* const currPar, const Operator* const currOp, xercesc::DOMElement* const parElement);
                void createInputs(const Operator* const currOp, xercesc::DOMElement* const opElement);
                
                const Stream* m_stream;
                std::string m_filename;
                xercesc::DOMImplementation* m_impl;
                xercesc::DOMDocument* m_doc;
                xercesc::DOMElement* m_strElement;
            };
        }
    }
}

#endif // STROM_XMLWRITERIMPL_H