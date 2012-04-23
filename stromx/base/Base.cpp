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

#include "AdjustRgbChannels.h"
#include "Base.h"
#include "Buffer.h"
#include "Camera.h"
#include "Canny.h"
#include "Clip.h"
#include "ConstImage.h"
#include "ConvertPixelType.h"
#include "Counter.h"
#include "Image.h"
#include "PeriodicDelay.h"
#include "Queue.h"
#include "Trigger.h"
#include <stromx/core/Registry.h>
#include <stromx/core/Exception.h>

void stromxRegisterBase(stromx::core::Registry& registry)
{
    using namespace stromx::base;
    
    registry.registerData(new Image);
    
    registry.registerOperator(new AdjustRgbChannels);
    registry.registerOperator(new Buffer);
    registry.registerOperator(new Camera);
    registry.registerOperator(new Canny);
    registry.registerOperator(new Clip);
    registry.registerOperator(new ConstImage);
    registry.registerOperator(new ConvertPixelType);
    registry.registerOperator(new Counter);
    registry.registerOperator(new PeriodicDelay);
    registry.registerOperator(new Queue);
    registry.registerOperator(new Trigger);
}