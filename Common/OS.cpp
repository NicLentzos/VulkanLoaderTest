//
//  OS.cpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#include "OS.hpp"
#include <iostream>

namespace VulkanApp {
namespace  OS{

Window::Window() : parameters(){}

Window::~Window(){
    Destroy();
}

WindowParameters Window::GetParameters() const {
    return parameters;
}

void Window::processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        std::cout << "W" << std::endl;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        std::cout << "S" << std::endl;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        std::cout << "A" << std::endl;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        std::cout << "D" << std::endl;
}

bool Window::RenderingLoop(){
    
    std::cout << "Rendering!" << std::endl;
    
    while (!glfwWindowShouldClose(parameters.window)) {
        // per-frame time logic
        // --------------------
        //float currentFrame = glfwGetTime();
        //deltaTime = currentFrame - lastFrame;
        //lastFrame = currentFrame;

        processInput(parameters.window);
        glfwPollEvents();
        //drawFrame();
    }
    
    return true;
}

void Window::Destroy(){
    
    std::cout << "Destroying window and terminating GLFW!" << std::endl;
    glfwDestroyWindow(parameters.window);
    glfwTerminate();
}

bool Window::Create(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    parameters.window = glfwCreateWindow(parameters.WIDTH, parameters.HEIGHT, parameters.title, nullptr, nullptr);
    glfwSetWindowUserPointer(parameters.window, this);
    glfwSetFramebufferSizeCallback(parameters.window, framebufferResizeCallback);
    glfwSetInputMode(parameters.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(parameters.window, mouse_callback);
    
    if(Window::parameters.window == nullptr){
        std::cout << "Unable to create GLFW window!" << std::endl;
        return false;
    }
    
    std::cout << "GLFW window created successfully!" << std::endl;
    return true;
}



void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height){
    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    app->parameters.frameBufferResized = true;
}

void Window::mouse_callback(GLFWwindow* window, double xPos, double yPos){
    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    
if (app->parameters.firstMouse)
    {
        app->parameters.lastX = app->parameters.xPos;
        app->parameters.lastY = app->parameters.yPos;
        app->parameters.firstMouse = false;
    }

    float xoffset = app->parameters.xPos - app->parameters.lastX;
    float yoffset = app->parameters.lastY - app->parameters.yPos; // reversed since y-coordinates go from bottom to top

    app->parameters.lastX = app->parameters.xPos;
    app->parameters.lastY = app->parameters.yPos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

}
}
