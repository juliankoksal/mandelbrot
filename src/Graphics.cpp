//
//  Graphics.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#include "Graphics.hpp"

void Graphics::initializeGL()
{
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(2.0 * ((double)WINDOW_SIZE / (double)PRECISION));
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (double)PRECISION, 0, (double)PRECISION, -1.0, 1.0);
}

void Graphics::drawPoints(std::array<std::array<int, PRECISION>, PRECISION>&
                          buffer)
{
    glBegin(GL_POINTS);
    for (int x = 0; x < PRECISION; ++x)
    {
        for (int y = 0; y < PRECISION; ++y)
        {
            drawPoint(x, y, buffer[x][y]);
        }
    }
    glEnd();
}

void Graphics::drawPoint(const double x, const double y, const int iteration)
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
