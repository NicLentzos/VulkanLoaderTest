//
//  Example.cpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#include "Example.hpp"
#include "VulkanFunctions.hpp"
#include <dlfcn.h>
#include <iostream>

namespace VulkanApp {

// Example class Constructor

Example::Example() : VulkanParameters(){
    
}

// Example class destructor

Example::~Example(){
    if(VulkanLibrary){
        dlclose(VulkanLibrary);
    }
}
/*
bool CheckAvailableInstanceExtensions(std::vector<VkExtensionProperties> available_extensions){
    uint32_t extensions_count = 0;
    VkResult result = VK_SUCCESS;
    
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, nullptr);
    
    if((result != VK_SUCCESS) || (extensions_count == 0)){
        std::cout << "Could not get number of instance extensions!" << std::endl;
        return false;
    }
    
    available_extensions.resize(extensions_count);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, available_extensions.data());
    
    if((result != VK_SUCCESS) || (extensions_count == 0)){
        std::cout << "Could not enumerate instance extensions!" << std::endl;
        return false;
    }
    
    return true;
}
*/
 
bool Example::LoadExportedEntryPoints(){
#define LoadProcAddress dlsym
#define VK_EXPORTED_FUNCTION( fun )                                         \
    if( !(fun = (PFN_##fun)LoadProcAddress( VulkanLibrary, #fun )) ) {      \
      std::cout << "Could not load exported function: " << #fun << "!" << std::endl;    \
      return false;                                                          \
    }

#include "VulkanFunctions.inl"
    
    std::cout << "Exported Entrypoints loaded!" << std::endl;
    
    return true;
}

bool Example::LoadGlobalLevelEntryPoints(){
#define VK_GLOBAL_LEVEL_FUNCTION( fun )                                                   \
    if( !(fun = (PFN_##fun)vkGetInstanceProcAddr( nullptr, #fun )) ) {                    \
      std::cout << "Could not load global level function: " << #fun << "!" << std::endl;  \
      return false;                                                                       \
    }
#include "VulkanFunctions.inl"
    
    std::cout << "Global Entrypoints loaded!" << std::endl;
    
    return true;
}


bool Example::CreateInstance(){
    VkApplicationInfo appInfo = {
        VK_STRUCTURE_TYPE_APPLICATION_INFO,             // VkStructureType            sType
        nullptr,                                        // const void                *pNext
        "Lentzos Vulkan app",  // const char                *pApplicationName
        VK_MAKE_VERSION( 1, 0, 0 ),                     // uint32_t                   applicationVersion
        "Lentzos engine",                     // const char                *pEngineName
        VK_MAKE_VERSION( 1, 0, 0 ),                     // uint32_t                   engineVersion
        VK_MAKE_VERSION( 1, 0, 0 )
    };
    
    VkInstanceCreateInfo createInfo = {
      VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,         // VkStructureType            sType
      nullptr,                                        // const void*                pNext
      0,                                              // VkInstanceCreateFlags      flags
      &appInfo,                                       // const VkApplicationInfo   *pApplicationInfo
      0,                                              // uint32_t                   enabledLayerCount
      nullptr,                                        // const char * const        *ppEnabledLayerNames
      0,                                              // uint32_t                   enabledExtensionCount
      nullptr                                         // const char * const        *ppEnabledExtensionNames
    };
    
    if(vkCreateInstance(&createInfo, nullptr, &VulkanParameters.instance) != VK_SUCCESS){
        std::cout << "Could not create Vulkan instance!";
        return false;
    }
    
    std::cout << "Vulkan instance created!" << std::endl;
    
    return true;
}

bool Example::LoadVulkanLibrary(){
    VulkanLibrary = dlopen("/usr/local/lib/libvulkan.1.2.141.dylib", RTLD_NOW);
    
    if(VulkanLibrary == nullptr){
        std::cout << "Could not load Vulkan library!" << std::endl;
        return false;
    }
    std::cout << "Vulkan library loaded!" << std::endl;
    return true;
}

bool Example::OnWindowSizeChanged(){
    // To do
    return true;
}

bool Example::Draw(){
    // to do
    return true;
}

bool Example::Prepare(){
    
    if(!LoadVulkanLibrary()){
        return false;
    }
    
    if(!LoadExportedEntryPoints()){
        return false;
    }
    
    if(!LoadGlobalLevelEntryPoints()){
        return false;
    }
    
    //if(!CheckAvailableInstanceExtensions(VulkanParameters.available_extensions)){
    //    return false;
    //}
    
    //if(!CreateInstance()){
    //    return false;
    //}
    
    return true;
}

} // Namespace VuklanApp
