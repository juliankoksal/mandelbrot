//
//  Algorithms.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#include "Algorithms.hpp"

std::complex<double> Algorithms::coordToComplex(const double x, const double y,
                                                const double scaleFactor,
                                                const double translateX,
                                                const double translateY)
{
    return std::complex<double>(x * scaleFactor + translateX,
                                y * scaleFactor + translateY);
};

int Algorithms::iterate(const std::complex<double>& c, std::complex<double> z)
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
