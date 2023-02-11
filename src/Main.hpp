//
//  Main.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#ifndef Main_hpp
#define Main_hpp

#include <GLFW/glfw3.h>

#include "Callbacks.hpp"
#include "Constants.hpp"
#include "Graphics.hpp"
#include "Mandelbrot.hpp"
#include "UserData.hpp"

/**
 * @brief Initializes the glfw window.
 *
 * @return pointer to the window that was created
 */
GLFWwindow* initializeWindow();

/**
 * @brief Deallocates resources and terminates GLFW.
 *
 * @param window glfw window
 */
void cleanupWindow(GLFWwindow* window);

#endif /* Main_hpp */
