//
//  Callbacks.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#include "Callbacks.hpp"

void Callbacks::keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        UserData& ud = *((UserData*)glfwGetWindowUserPointer(window));
        switch (key)
        {
            case GLFW_KEY_LEFT:
                ud.translateX -= ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_RIGHT:
                ud.translateX += ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_DOWN:
                ud.translateY -= ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_UP:
                ud.translateY += ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_Z:
                ud.scaleFactor *= ZOOM_STEP;
                ud.translateX -= ud.scaleFactor * PAN;
                ud.translateY -= ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_X:
                ud.scaleFactor /= ZOOM_STEP;
                ud.translateX += ud.scaleFactor * PAN;
                ud.translateY += ud.scaleFactor * PAN;
                break;
            case GLFW_KEY_ESCAPE:
                ud.loadDefaultValues();
                break;
            default:
                return;
        }
    }
}

void Callbacks::mouseButtonCallback(GLFWwindow* window, int button, int action,
                                    int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        UserData& ud = *((UserData*)glfwGetWindowUserPointer(window));
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        cursorX *= WINDOW_COORD_FACTOR;
        cursorY = ((double)WINDOW_SIZE - cursorY) * WINDOW_COORD_FACTOR;
        ud.pointClicked = Algorithms::coordToComplex(cursorX, cursorY,
                                                     ud.scaleFactor,
                                                     ud.translateX,
                                                     ud.translateY);
        ud.isJuliaSet = !ud.isJuliaSet;
    }
}
