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

#include <python/stromx/runtime/ExportOperatorKernel.h>

#include <boost/python.hpp>

#include <stromx/runtime/Registry.h>
#include <stromx/cvsupport/Cvsupport.h>
#include <stromx/cvsupport/Buffer.h>
#include <stromx/cvsupport/ConstImage.h>
#include <stromx/cvsupport/AdjustRgbChannels.h>
#include <stromx/cvsupport/Camera.h>
#include <stromx/cvsupport/ConvertPixelType.h>
#include <stromx/cvsupport/Clip.h>

void exportImage();
void exportMatrix();

using namespace boost::python;
using namespace stromx::cvsupport;
    
BOOST_PYTHON_MODULE(libcvsupport)
{
    def("registerCvsupport", stromxRegisterCvsupport);
    
    exportImage();
    exportMatrix();
    
    stromx::python::exportOperatorKernel<AdjustRgbChannels>("AdjustRgbChannels");
    stromx::python::exportOperatorKernel<Buffer>("Buffer");
    stromx::python::exportOperatorKernel<Camera>("Camera");
    stromx::python::exportOperatorKernel<Clip>("Clip");
    stromx::python::exportOperatorKernel<ConstImage>("ConstImage");
    stromx::python::exportOperatorKernel<ConvertPixelType>("ConvertPixelType");
}