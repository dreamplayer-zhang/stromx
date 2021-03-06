/* 
*  Copyright 2012 Matthias Fuchs
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

#include <cppunit/TestAssert.h>
#include "stromx/runtime/ConstDataRef.h"
#include "stromx/runtime/DataRef.h"
#include "stromx/runtime/None.h"
#include "stromx/runtime/test/DataRefTest.h"
#include "stromx/runtime/test/TestData.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::runtime::DataRefTest);

namespace stromx
{
    namespace runtime
    {
        void DataRefTest::testDataRef()
        {
            DataRef ref(new TestData(5));
            DataRef copy(ref);
            DataRef empty;
            empty = copy;
            
            dataFunction(ref);
            
            CPPUNIT_ASSERT_EQUAL(int(5), data_cast<TestData>(empty).value());
        }
        
        void DataRefTest::testConstDataRef()
        {
            ConstDataRef constRef(new TestData(5));
            ConstDataRef copy(constRef);
            ConstDataRef empty;
            empty = copy;
            
            dataFunction(constRef);
            
            CPPUNIT_ASSERT_EQUAL(int(5), data_cast<TestData>(empty).value());
        }
        
        void DataRefTest::testIsNull()
        {
            CPPUNIT_ASSERT(! DataRef(new TestData()).isNull());
            CPPUNIT_ASSERT(DataRef().isNull());
        }
    }
}
