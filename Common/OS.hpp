//
//  OS.hpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#ifndef OS_hpp
#define OS_hpp

#if defined(VK_USE_PLATFORM_MACOS_KHR)
#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include "vulkan.h"
#include "glfw3.h"
#endif

#include <vector>

namespace VulkanApp {
namespace OS{

#if defined(VK_USE_PLATFORM_MACOS_KHR)
    typedef void* LibraryHandle;
#endif

struct WindowParameters{

    GLFWwindow* window;
    uint32_t WIDTH;
    uint32_t HEIGHT;
    const char* title;
    bool frameBufferResized;
    bool firstMouse;
    float lastX;
    float lastY;
    float deltaTime;
    float xPos;
    float yPos;

    WindowParameters():
        WIDTH(800),
        HEIGHT(600),
        title("Vulkan Window"),
        frameBufferResized(false),
        firstMouse(true){}
};

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

class Base{
public:
    Base(){
        CanRender = false;
    }
        
    virtual ~Base(){
            
    }
        
    virtual bool OnWindowSizeChanged() = 0;
    virtual bool Draw() = 0;
    virtual bool ReadyToDraw(){
        return CanRender;
    }
        
protected:
    bool CanRender;
};

class Example:public Base{
public:
    Example();
    
    ~Example();
    
    bool OnWindowSizeChanged() override;
    bool Draw() override;
    bool Prepare();
    
private:
    VulkanApp::OS::LibraryHandle VulkanLibrary;
    ExampleParameters VulkanParameters;
    
    bool LoadVulkanLibrary();
    bool LoadExportedEntryPoints();
    bool LoadGlobalLevelEntryPoints();
    //bool CheckAvailableInstanceExtensions(std::vector<VkExtensionProperties> &available_extensions);
    bool CreateInstance();
};

class Window{
public:
    
    Window();
    
    ~Window();
    
    bool Create();
    bool RenderingLoop();
    void Destroy();
    WindowParameters GetParameters() const;
    
private:
    WindowParameters parameters;
    
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    void processInput(GLFWwindow* window);
};

} // Namespace OS

} // Namespace VulkanApp

#endif /* OS_hpp */
