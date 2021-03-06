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

#include <stromx/runtime/Factory.h>
#include <stromx/runtime/XmlReader.h>
#include <stromx/runtime/Stream.h>
#include <stromx/runtime/Runtime.h>
#include <stromx/runtime/Operator.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/Image.h>

#include <stromx/cvsupport/Cvsupport.h>

#include <iostream>

using namespace stromx;

int main (int, char**)
{
    runtime::Factory factory;
    
    stromxRegisterRuntime(&factory);
    stromxRegisterCvsupport(&factory);
    
    runtime::Stream* stream = runtime::XmlReader().readStream("camera.xml", &factory);
    
    stream->start();
    
    runtime::Operator* camera = stream->operators()[0];
    runtime::Operator* convertPixelType = stream->operators()[2];
    
    for(unsigned int i = 0; i < 5; ++i)
    {
        runtime::DataContainer data = convertPixelType->getOutputData(2);
        runtime::ReadAccess image(data);
        std::cout << "Received image " 
                  << image.get<runtime::Image>().height() << "x"
                  << image.get<runtime::Image>().width() << ", "
                  << image.get().variant().title() << std::endl;
        
        convertPixelType->clearOutputData(2);
        camera->clearOutputData(1);
    }
    
    stream->stop();
    stream->join();
    
    delete stream;
}
