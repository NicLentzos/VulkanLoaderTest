//
//  Example.hpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#ifndef Example_hpp
#define Example_hpp

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include "vulkan.h"
#include "OS.hpp"

namespace VulkanApp {

struct ExampleParameters{
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    std::vector<VkExtensionProperties> available_extensions;
    
    ExampleParameters():
        instance(VK_NULL_HANDLE),
        physicalDevice(VK_NULL_HANDLE),
        device(VK_NULL_HANDLE){}
};

class Example:public OS::Base{
public:
    Example();
    
    ~Example();
    
    bool OnWindowSizeChanged() override;
    bool Draw() override;
    bool Prepare();
    
private:
    OS::LibraryHandle VulkanLibrary;
    ExampleParameters VulkanParameters;
    
    bool LoadVulkanLibrary();
    bool LoadExportedEntryPoints();
    bool LoadGlobalLevelEntryPoints();
    //bool CheckAvailableInstanceExtensions(std::vector<VkExtensionProperties> &available_extensions);
    bool CreateInstance();
};
}

#endif /* Example_hpp */
