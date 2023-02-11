//
//  Algorithms.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#ifndef Algorithms_hpp
#define Algorithms_hpp

#include <complex>

#include "Constants.hpp"

namespace Algorithms
{

/**
 * @brief Converts world coordinate to a complex number.
 *
 * @param x world x-coordinate
 * @param y world y-coordinate
 * @param scaleFactor factor to scale by
 * @param translateX translate x by this amount after scaling
 * @param translateY translate y by this amount after scaling 
 */
std::complex<double> coordToComplex(const double x, const double y,
                                    const double scaleFactor,
                                    const double translateX,
                                    const double translateY);

/**
 * @brief Iterates the Mandelbrot function for the given value of c and z0.
 *
 * @param c constant
 * @param z initial value of z
 *
 * @return number of iterations to diverge, up to MAX_ITERATIONS
 */
int iterate(const std::complex<double>& c, std::complex<double> z);

}

#endif /* Algorithms_hpp */
