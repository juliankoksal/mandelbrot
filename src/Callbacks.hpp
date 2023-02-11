//
//  Callbacks.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#ifndef Callbacks_hpp
#define Callbacks_hpp

#include <GLFW/glfw3.h>

#include "Algorithms.hpp"
#include "Constants.hpp"
#include "UserData.hpp"

namespace Callbacks
{

/**
 * @brief Callback function for key event.
 *
 * Adjusts projection matrix according to the key pushed and redraws the set.
 *     up/down: pan up/down
 *     right/left: pan right/left
 *     x/z: zoom in/out
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods);

/**
 * @brief Callback function for mouse button event.
 *
 * Draws the Julia set for the point that was clicked or redraws the Mandelbrot
 * set if the window is clicked again.
 */
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

}

#endif /* Callbacks_hpp */
