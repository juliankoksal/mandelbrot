//
//  Mandelbrot.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#include "Mandelbrot.hpp"

void Mandelbrot::calculateSet(UserData& ud)
{
#ifndef GRADIENT
    if (ud.isJuliaSet)
    {
        calculateJuliaPoints(ud);
    }
    else
    {
        calculateMandelbrotPoints(ud);
    }
#else
    calculateGradientPoints(ud);
#endif
}

void Mandelbrot::calculateMandelbrotPoints(UserData& ud)
{
    std::array<std::thread, NUM_THREADS - 1> threads;
    for (int i = 1; i < NUM_THREADS; ++i)
    {
        threads[i - 1] = std::thread(calculateMandelbrotPointsThread,
                                     std::ref(ud), i);
    }
    calculateMandelbrotPointsThread(ud, 0);
    for (int i = 1; i < NUM_THREADS; ++i)
    {
        threads[i - 1].join();
    }
}

void Mandelbrot::calculateMandelbrotPointsThread(UserData& ud, int start)
{
    std::complex<double> z0(0.0, 0.0);
    for (int pX = start; pX < PRECISION; pX += NUM_THREADS)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            const std::complex<double> c = Algorithms::coordToComplex(pX, pY,
                                                              ud.scaleFactor,
                                                              ud.translateX,
                                                              ud.translateY);
            ud.renderBuffer[pX][pY] = Algorithms::iterate(c, z0);
        }
    }
}

void Mandelbrot::calculateJuliaPoints(UserData& ud)
{
    std::array<std::thread, NUM_THREADS - 1> threads;
    for (int i = 1; i < NUM_THREADS; ++i)
    {
        threads[i - 1] = std::thread(calculateJuliaPointsThread,
                                     std::ref(ud), i);
    }
    calculateJuliaPointsThread(ud, 0);
    for (int i = 1; i < NUM_THREADS; ++i)
    {
        threads[i - 1].join();
    }
}

void Mandelbrot::calculateJuliaPointsThread(UserData& ud, int start)
{
    for (int pX = start; pX < PRECISION; pX += NUM_THREADS)
    {
        for (int pY = 0; pY < PRECISION; ++pY)
        {
            std::complex<double> z0 = Algorithms::coordToComplex(pX, pY,
                                                                 ud.scaleFactor,
                                                                 ud.translateX,
                                                                 ud.translateY);
            ud.renderBuffer[pX][pY] = Algorithms::iterate(ud.pointClicked, z0);
        }
    }
}

void Mandelbrot::calculateGradientPoints(UserData& ud)
{
    for (int x = 0; x < PRECISION; ++x)
    {
        for (int y = 0; y < PRECISION; ++y)
        {
            ud.renderBuffer[x][y] = x;
        }
    }
};
