//
//  Main.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#include "Main.hpp"

GLFWwindow* initializeWindow()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE,
                                          "Mandelbrot Set", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return window;
    }
    glfwMakeContextCurrent(window);
    
    UserData* ud = new UserData();
    
    glfwSetWindowUserPointer(window, ud);
    glfwSetKeyCallback(window, Callbacks::keyCallback);
    glfwSetMouseButtonCallback(window, Callbacks::mouseButtonCallback);
    
    return window;
}

void cleanupWindow(GLFWwindow* window)
{
    delete (UserData*)glfwGetWindowUserPointer(window);
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main(int argc, const char* argv[])
{
    if (!glfwInit())
    {
        return -1;
    }
    GLFWwindow* window = initializeWindow();
    if (!window)
    {
        return -1;
    }
    
    UserData& ud = *(UserData*)glfwGetWindowUserPointer(window);
    
    Graphics::initializeGL();
    
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();
        Mandelbrot::calculateSet(ud);
        Graphics::drawPoints(ud.renderBuffer);
        glfwSwapBuffers(window);
    }
    
    cleanupWindow(window);
    
    return 0;
}
