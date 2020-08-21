//
//  VulkanFunctions.hpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#ifndef VulkanFunctions_hpp
#define VulkanFunctions_hpp

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif

#include "vulkan.h"

namespace VulkanApp {
#define VK_EXPORTED_FUNCTION( fun ) extern PFN_##fun fun;
#define VK_GLOBAL_LEVEL_FUNCTION( fun) extern PFN_##fun fun;
#define VK_INSTANCE_LEVEL_FUNCTION( fun ) extern PFN_##fun fun;
#define VK_DEVICE_LEVEL_FUNCTION( fun ) extern PFN_##fun fun;

#include "VulkanFunctions.inl"
}

#endif /* VulkanFunctions_hpp */
