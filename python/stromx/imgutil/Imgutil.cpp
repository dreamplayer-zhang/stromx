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

#include "../runtime/ExportOperatorKernel.h"

#include <boost/python.hpp>

#include <stromx/runtime/Registry.h>
#include <stromx/imgutil/Imgutil.h>
#include <stromx/imgutil/Buffer.h>
#include <stromx/imgutil/ConstImage.h>
#include <stromx/imgutil/AdjustRgbChannels.h>
#include <stromx/imgutil/Camera.h>
#include <stromx/imgutil/ConvertPixelType.h>
#include <stromx/imgutil/Clip.h>

void exportImage();
void exportMatrix();

using namespace boost::python;
using namespace stromx::imgutil;
    
BOOST_PYTHON_MODULE(libimgutil)
{
    def("registerImgutil", stromxRegisterImgutil);
    
    exportImage();
    exportMatrix();
    
    stromx::python::exportOperatorKernel<AdjustRgbChannels>("AdjustRgbChannels");
    stromx::python::exportOperatorKernel<Buffer>("Buffer");
    stromx::python::exportOperatorKernel<Camera>("Camera");
    stromx::python::exportOperatorKernel<Clip>("Clip");
    stromx::python::exportOperatorKernel<ConstImage>("ConstImage");
    stromx::python::exportOperatorKernel<ConvertPixelType>("ConvertPixelType");
}