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

#ifndef STROMX_RUNTIME_SERVERTEST_H
#define STROMX_RUNTIME_SERVERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/impl/Server.h"

namespace stromx
{
    namespace runtime
    {
        class OperatorTester;
        
        class ServerTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (ServerTest);
            CPPUNIT_TEST (testConstructor);
            CPPUNIT_TEST (testConnect); 
            CPPUNIT_TEST (testConnectFails);
            CPPUNIT_TEST (testReceive);  
            CPPUNIT_TEST (testReceiveMultipleData);
            CPPUNIT_TEST (testConstructorFails);
            CPPUNIT_TEST_SUITE_END ();

        public:
            ServerTest() : m_server(0) {}
            
            void setUp();
            void tearDown();

        protected:
            void testConstructor();
            void testConnect();
            void testConnectFails();
            void testReceive();
            void testReceiveMultipleData();
            void testConstructorFails();
                
        private:            
            impl::Server* m_server;
        };
    }
}

#endif // STROMX_RUNTIME_SERVERTEST_H