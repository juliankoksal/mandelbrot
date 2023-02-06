//
//  Mandelbrot.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <complex>
#include <string>

#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "UserData.hpp"

/**
 * @brief Initializes the window and sets initial OpenGL state.
 *
 * @return pointer to the window that was created
 */
GLFWwindow* initialize()
{
    GLFWwindow* window = glfwCreateWindow(800, 800, "Mandelbrot Set", NULL,
                                          NULL);
    if (!window)
    {
        glfwTerminate();
        return window;
    }
    glfwMakeContextCurrent(window);

    // Viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, PRECISION, 0, PRECISION, -1.0, 1.0);

    glClearColor(0.0, 0.0, 0.5, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2 * (800 / PRECISION));
    
    return window;
}

/**
 * @brief Draws a point at (pX, pY) with the colour determined by iteration.
 *
 * @param pX x-coordinate of the point in world coordinates
 * @param pY y-coordinate of the point in world coordinates
 * @param iteration number of iterations calculated for this point
 */
inline void drawPoint(double pX, double pY, int iteration)
{
    if (iteration == MAX_ITERATION)
    {
        glColor3d(0.0, 0.0, 0.0);
    }
    else if (iteration < SECONDARY_COLOUR_ITERATION_CUTOFF)
    {
        glColor3d(R_SECONDARY[iteration], G_SECONDARY[iteration],
                  B_SECONDARY[iteration]);
    }
    else
    {
        glColor3d(1.0, G_PRIMARY[iteration], B_PRIMARY[iteration]);
    }

    glVertex2d(pX, pY);
}

/**
 * @brief Converts a world coordinate to a complex number.
 *
 * @param pX world x-coordinate
 * @param pY world y-coordinate
 * @param ud user data giving the scale and translation parameters
 *
 * @return complex number corresponding to (pX, pY)
 */
inline std::complex<long double> worldCoordToComplex(int pX, int pY,
                                                UserData* ud)
{
    long double x = (long double)pX * ud->getScale() + ud->getTranslateX();
    long double y = (long double)pY * ud->getScale() + ud->getTranslateY();
    return std::complex<long double>(x, y);
}

/**
 * @brief Iterates the Mandelbrot function for the given point.
 *
 * @param c constant
 * @param z initial value of z
 *
 * @return number of iterations to diverge, up to MAX_ITERATIONS
 */
inline int iterate(const std::complex<long double>& c,
                   std::complex<long double> z)
{
    int iteration = 0;
    while (std::norm(z) <= 4 && iteration < MAX_ITERATION)
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
void drawMandelbrotPoints(UserData* ud)
{
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            std::complex<long double> c(worldCoordToComplex(pX, pY, ud));
            std::complex<long double> z0(0.0, 0.0);
            drawPoint(pX, pY, iterate(c, z0));
        }
    }
}

/**
 * @brief Draws the points of the Julia set for the point that was clicked.
 *
 * @param ud user data giving the scale and translation parameters
 */
void drawJuliaPoints(UserData* ud)
{
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            std::complex<long double> c(ud->getPointClicked());
            std::complex<long double> z0(worldCoordToComplex(pX, pY, ud));
            drawPoint(pX, pY, iterate(c, z0));
        }
    }
}

/**
 * @brief Draws the Mandelbrot/Julia set.
 *
 * @param window glfw window
 */
void drawSet(GLFWwindow* window)
{
    UserData* ud = (UserData*)glfwGetWindowUserPointer(window);
    ud->setIsDrawingFrame();
    glBegin(GL_POINTS);
    if (ud->getIsJuliaSet())
    {
        drawJuliaPoints(ud);
    }
    else
    {
        drawMandelbrotPoints(ud);
    }
    glEnd();
    glfwSwapBuffers(window);
    ud->setIsDrawingFrame(false);
}

/**
 * @brief Callback function for key event.
 *
 * Adjusts user data according to the key pushed and redraws the set.
 *     up/down: translate up/down
 *     right/left: translate right/left
 *     x/z: zoom in/out
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods)
{
    if (action == GLFW_PRESS)
    {
        UserData* ud = ((UserData*)glfwGetWindowUserPointer(window));
        if (ud->getIsDrawingFrame())
        {
            return;
        }
        switch (key)
        {
            case GLFW_KEY_UP:
                ud->setCentreY(ud->getCentreY() + PAN_STEP / ud->getZoom());
                break;
            case GLFW_KEY_DOWN:
                ud->setCentreY(ud->getCentreY() - PAN_STEP / ud->getZoom());
                break;
            case GLFW_KEY_RIGHT:
                ud->setCentreX(ud->getCentreX() + PAN_STEP / ud->getZoom());
                break;
            case GLFW_KEY_LEFT:
                ud->setCentreX(ud->getCentreX() - PAN_STEP / ud->getZoom());
                break;
            case GLFW_KEY_X:
                ud->setZoom(ud->getZoom() * ZOOM_STEP);
                break;
            case GLFW_KEY_Z:
                ud->setZoom(ud->getZoom() / ZOOM_STEP);
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
 * set if it is the second click.
 */
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        UserData* ud = ((UserData*)glfwGetWindowUserPointer(window));
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        ud->setIsJuliaSet(!ud->getIsJuliaSet());
        ud->setPointClicked(worldCoordToComplex(cursorX, cursorY, ud));
        drawSet(window);
    }
}

int main(int argc, const char* argv[])
{
    if (!glfwInit())
    {
        return -1;
    }
    GLFWwindow* window = initialize();
    if (!window)
    {
        return -1;
    }
    
    UserData ud(PRECISION);
    if (argc >= 2)
    {
        ud.setZoom(std::stold(argv[1]));
    }
    if (argc >= 3)
    {
        ud.setCentreX(std::stold(argv[2]));
    }
    if (argc >= 4)
    {
        ud.setCentreY(std::stold(argv[3]));
    }
    
    glfwSetWindowUserPointer(window, &ud);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    drawSet(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
