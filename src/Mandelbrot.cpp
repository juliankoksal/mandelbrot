//
//  Mandelbrot.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#define GL_SILENCE_DEPRECATION

#include <complex>

#include <GLFW/glfw3.h>

#include "Constants.hpp"
#include "UserData.hpp"

/**
 * @brief Draws a point at (x, y) with the colour determined by iteration.
 *
 * @param x x-coordinate of the point
 * @param y y-coordinate of the point
 * @param iteration number of iterations calculated for this point
 */
inline void drawPoint(const double x, const double y, const int iteration)
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
inline int iterate(const std::complex<double>& c, std::complex<double> z)
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
void drawMandelbrotPoints(UserData* ud)
{
    double step = (ud->viewRight - ud->viewLeft) / PRECISION;
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            const std::complex<double> c(ud->viewLeft + (double)pX * step,
                                         ud->viewBottom + (double)pY * step);
            std::complex<double> z0(0.0, 0.0);
            drawPoint(c.real(), c.imag(), iterate(c, z0));
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
    double step = (ud->viewRight - ud->viewLeft) / PRECISION;
    for (int pX = 0; pX < PRECISION; ++pX)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            const std::complex<double> c(ud->pointClicked);
            std::complex<double> z0(ud->viewLeft + (double)pX * step,
                                    ud->viewBottom + (double)pY * step);
            drawPoint(z0.real(), z0.imag(), iterate(c, z0));
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
    glBegin(GL_POINTS);
    if (ud->isJuliaSet)
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
        UserData* ud = ((UserData*)glfwGetWindowUserPointer(window));
        double viewSize = (ud->viewRight - ud->viewLeft);
        double pan = PAN_STEP * viewSize;
        double viewCentreX = (ud->viewLeft + ud->viewRight) / 2.0;
        double viewCentreY = (ud->viewBottom + ud->viewTop) / 2.0;
        switch (key)
        {
            case GLFW_KEY_UP:
                ud->viewBottom += pan;
                ud->viewTop += pan;
                break;
            case GLFW_KEY_DOWN:
                ud->viewBottom -= pan;
                ud->viewTop -= pan;
                break;
            case GLFW_KEY_RIGHT:
                ud->viewLeft += pan;
                ud->viewRight += pan;
                break;
            case GLFW_KEY_LEFT:
                ud->viewLeft -= pan;
                ud->viewRight -= pan;
                break;
            case GLFW_KEY_X:
                viewSize /= ZOOM_STEP;
                ud->viewLeft = viewCentreX - viewSize / 2.0;
                ud->viewRight = viewCentreX + viewSize / 2.0;
                ud->viewBottom = viewCentreY - viewSize / 2.0;
                ud->viewTop = viewCentreY + viewSize / 2.0;
                break;
            case GLFW_KEY_Z:
                viewSize *= ZOOM_STEP;
                ud->viewLeft = viewCentreX - viewSize / 2.0;
                ud->viewRight = viewCentreX + viewSize / 2.0;
                ud->viewBottom = viewCentreY - viewSize / 2.0;
                ud->viewTop = viewCentreY + viewSize / 2.0;
                break;
            case GLFW_KEY_ESCAPE:
                ud->loadDefaultValues();
                break;
            default:
                return;
        }
        glLoadIdentity();
        glOrtho(ud->viewLeft, ud->viewRight, ud->viewBottom, ud->viewTop, -1.0,
                1.0);
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
        UserData* ud = ((UserData*)glfwGetWindowUserPointer(window));
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        const double scaleFactor = (ud->viewRight - ud->viewLeft) / (double)WINDOW_SIZE;
        cursorX = cursorX * scaleFactor + ud->viewLeft;
        cursorY = -1.0 * cursorY * scaleFactor + ud->viewTop;
        ud->pointClicked = std::complex<double>(cursorX, cursorY);
        ud->isJuliaSet = !ud->isJuliaSet;
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
    UserData* ud = (UserData*)glfwGetWindowUserPointer(window);
    
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(2.0 * ((double)WINDOW_SIZE / PRECISION));
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(ud->viewLeft, ud->viewRight, ud->viewBottom, ud->viewTop, -1.0,
            1.0);
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
