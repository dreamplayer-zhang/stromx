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

#ifndef STROMX_RUNTIME_TESTUTILITIES_H
#define STROMX_RUNTIME_TESTUTILITIES_H


namespace stromx
{
    namespace runtime
    {
        class Stream;
        
        class TestUtilities
        {
        public:
            static Stream* buildTestStream();
        };
        
    }
}

#endif // STROMX_RUNTIME_TESTUTILITIES_H 