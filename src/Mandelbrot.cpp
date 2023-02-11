//
//  Mandelbrot.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>

#include <complex>

#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "UserData.hpp"

std::complex<double> coordToComplex(const double x, const double y,
                                    UserData& ud)
{
    return std::complex<double>(x * ud.scaleFactor + ud.translateX,
                                y * ud.scaleFactor + ud.translateY);
};

/**
 * @brief Draws a point at (x, y) with the colour determined by iteration.
 *
 * @param x x-coordinate of the point
 * @param y y-coordinate of the point
 * @param iteration number of iterations calculated for this point
 */
void drawPoint(const double x, const double y, const int iteration)
{
    if (iteration == MAX_ITERATION)
    {
        glColor3d(0.0, 0.0, 0.0);
    }
    else if (iteration < SECONDARY_COLOUR_IT_CUTOFF)
    {
        glColor3d(SECONDARY_COLOUR[iteration].R,
                  SECONDARY_COLOUR[iteration].G,
                  SECONDARY_COLOUR[iteration].B);
    }
    else
    {
        glColor3d(PRIMARY_COLOUR[iteration].R,
                  PRIMARY_COLOUR[iteration].G,
                  PRIMARY_COLOUR[iteration].B);
    }

    glVertex2d(x, y);
}

/**
 * @brief Iterates the Mandelbrot function for the given value of c and z0.
 *
 * @param c constant
 * @param z initial value of z
 *
 * @return number of iterations to diverge, up to MAX_ITERATIONS
 */
int iterate(const std::complex<double>& c, std::complex<double> z)
{
    int iteration = 0;
    while (std::norm(z) <= 4.0 && iteration < MAX_ITERATION)
    {
        z *= z;
        z += c;
        ++iteration;
    }
    return iteration;
}

/**
 * @brief Draws the points of the Mandelbrot set.
 *
 * @param ud user data giving the scale and translation parameters
 */
void drawMandelbrotPoints(UserData& ud)
{
    ud.allPointsMaxIterations = true;
    std::complex<double> z0(0.0, 0.0);
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            const std::complex<double> c = coordToComplex(pX, pY, ud);
            int iterations = iterate(c, z0);
            if (iterations < MAX_ITERATION)
            {
                ud.allPointsMaxIterations = false;
                ud.allPointsMaxIterationsScaleFactor = ud.scaleFactor;
            }
            drawPoint(pX, pY, iterations);
        }
    }
}

/**
 * @brief Draws the points of the Julia set for the point that was clicked.
 *
 * @param ud user data giving the scale and translation parameters
 */
void drawJuliaPoints(UserData& ud)
{
    ud.allPointsMaxIterations = true;
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            std::complex<double> z0 = coordToComplex(pX, pY, ud);
            int iterations = iterate(ud.pointClicked, z0);
            if (iterations < MAX_ITERATION)
            {
                ud.allPointsMaxIterations = false;
                ud.allPointsMaxIterationsScaleFactor = ud.scaleFactor;
            }
            drawPoint(pX, pY, iterations);
        }
    }
}

/**
 * @brief Draws the Mandelbrot/Julia set.
 *
 * @param window GLFW window
 */
void drawSet(GLFWwindow* window)
{
    UserData& ud = *(UserData*)glfwGetWindowUserPointer(window);
    glBegin(GL_POINTS);
    if (ud.isJuliaSet)
    {
        drawJuliaPoints(ud);
    }
    else
    {
        drawMandelbrotPoints(ud);
    }
    glEnd();
    glfwSwapBuffers(window);
}

/**
 * @brief Callback function for key event.
 *
 * Adjusts projection matrix according to the key pushed and redraws the set.
 *     up/down: pan up/down
 *     right/left: pan right/left
 *     x/z: zoom in/out
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods)
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
                if (ud.scaleFactor < ud.allPointsMaxIterationsScaleFactor)
                {
                    return;
                }
                break;
            case GLFW_KEY_X:
                ud.scaleFactor /= ZOOM_STEP;
                ud.translateX += ud.scaleFactor * PAN;
                ud.translateY += ud.scaleFactor * PAN;
                if (ud.allPointsMaxIterations)
                {
                    return;
                }
                break;
            case GLFW_KEY_ESCAPE:
                ud.loadDefaultValues();
                break;
            default:
                return;
        }
        drawSet(window);
    }
}

/**
 * @brief Callback function for mouse button event.
 *
 * Draws the Julia set for the point that was clicked or redraws the Mandelbrot
 * set if the window is clicked again.
 */
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        UserData& ud = *((UserData*)glfwGetWindowUserPointer(window));
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        ud.pointClicked = coordToComplex(cursorX, PRECISION - cursorY, ud);
        ud.isJuliaSet = !ud.isJuliaSet;
        drawSet(window);
    }
}

/**
 * @brief Initializes the glfw window.
 *
 * @return pointer to the window that was created
 */
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
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    return window;
}

/**
 * @brief Sets the initial OpenGL state.
 *
 * @param window glfw window
 */
void initializeGL(GLFWwindow* window)
{
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(2.0 * ((double)WINDOW_SIZE / PRECISION));
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, PRECISION, 0, PRECISION, -1.0, 1.0);
}

/**
 * @brief Deallocates resources and terminates GLFW.
 *
 * @param window glfw window
 */
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
    
    initializeGL(window);
    
    drawSet(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();
    }
    
    cleanupWindow(window);
    
    return 0;
}
