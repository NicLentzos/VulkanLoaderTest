//
//  main.cpp
//  GLFWLoader2
//
//  Created by Nicholas Lentzos on 21/08/2020.
//  Copyright © 2020 Nicholas Lentzos. All rights reserved.
//

#include "Example.hpp"

int main(int argc, const char * argv[]) {
    
    VulkanApp::OS::Window window;
    VulkanApp::Example example;
    
    if(!window.Create()){
        return -1;
    }
    
    if(!example.Prepare()){
        return -1;
    }
    
    if(!window.RenderingLoop()){
        return -1;
    }
    
    return 0;
}

