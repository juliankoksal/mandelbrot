//
//  Graphics.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#ifndef Graphics_hpp
#define Graphics_hpp

#include <GL/gl.h>

#include "Constants.hpp"

namespace Graphics
{

/**
 * @brief Sets the initial OpenGL state.
 */
void initializeGL();

/**
 * @brief Draws all points in the buffer.
 *
 * @param buffer array of iteration counts for each point
 */
void drawPoints(std::array<std::array<int, PRECISION>, PRECISION>& buffer);

/**
 * @brief Draws a point at (x, y) with the colour determined by iteration.
 *
 * @param x x-coordinate of the point
 * @param y y-coordinate of the point
 * @param iteration number of iterations calculated for this point
 */
void drawPoint(const double x, const double y, const int iteration);

}

#endif /* Graphics_hpp */
