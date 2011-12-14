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

#include "Exception.h"
#include "Operator.h"
#include "Thread.h"
#include "impl/InputNode.h"
#include "impl/Network.h"
#include "impl/ThreadImpl.h"

namespace stromx
{
    namespace core
    {
        using namespace impl;
        
        Thread::Thread(const core::impl::Network*const network)
          : m_thread(0),
            m_network(network)
        {
            if(! network)
                throw WrongArgument("Passed null pointer as network.");
            
            m_thread = new impl::ThreadImpl;
        }
        
        Thread::~Thread()
        {
            delete m_thread;
        }
        
        const Thread::Status Thread::status() const 
        { 
            return Status(m_thread->status());
        }
        
        const std::string & Thread::name() const
        {
            return m_name; 
        }
        
        void Thread::setName(const std::string& name)
        { 
            m_name = name; 
        }
        
        const std::vector<Input> & Thread::inputSequence() const
        { 
            return m_inputSequence;
        }
        
        void Thread::start()
        {
            m_thread->start();
        }
        
        void Thread::stop()
        {
            m_thread->stop(); 
        }
        
        void Thread::join()
        { 
            m_thread->join();
        }
        
        void Thread::pause()
        {
            m_thread->pause();
        }

        void Thread::resume()
        {
            m_thread->resume();
        }

        void Thread::removeOperator(const Operator* op)
        {
            typedef std::set< std::vector<Input>::iterator > IndexSet;
            
            IndexSet toBeErased;
            
            for(std::vector<Input>::iterator iter = m_inputSequence.begin();
                iter != m_inputSequence.end();
                ++iter)
            {
                if((*iter).op() == op)
                    toBeErased.insert(iter);
            }
            
            for(IndexSet::iterator iter = toBeErased.begin();
                iter != toBeErased.end();
                ++iter)
            {
                m_inputSequence.erase(*iter);
            }
            
            m_thread->removeOperator(op);
        }
            
        void Thread::addInput(Operator* const op, const unsigned int inputId)
        {
            InputNode* inputNode = m_network->getInputNode(op, inputId);
            m_thread->addInput(inputNode);
            m_inputSequence.push_back(Input(op, inputId));
        }

        void Thread::insertInput(const unsigned int position, Operator* const op, const unsigned int inputId)
        {
            InputNode* inputNode = m_network->getInputNode(op, inputId);
            m_thread->insertInput(position, inputNode);
            m_inputSequence.insert(m_inputSequence.begin() + position, Input(op, inputId));
        }

        void Thread::removeInput(const unsigned int position)
        {
            m_thread->removeInput(position);
            m_inputSequence.erase(m_inputSequence.begin() + position);
        }
    } 
}
