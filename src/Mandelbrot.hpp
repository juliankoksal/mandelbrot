//
//  Mandelbrot.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-11.
//

#ifndef Mandelbrot_h
#define Mandelbrot_h

#include <thread>

#include "Algorithms.hpp"
#include "UserData.hpp"

namespace Mandelbrot
{

/**
 * @brief Calculates Mandelbrot/Julia set, writes results to ud.renderBuffer.
 *
 * @param ud user data, results are written to renderBuffer
 */
void calculateSet(UserData& ud);

/**
 * @brief Calculates Mandelbrot set, writes results to ud.renderBuffer.
 *
 * @param ud user data, results are written to renderBuffer
 */
void calculateMandelbrotPoints(UserData& ud);

/**
 * @brief Calculates a part of the set based on the number of threads.
 *
 * @param ud user data, results are written to renderBuffer
 * @param start calculates every [number of threads] points, starting from here
 */
void calculateMandelbrotPointsThread(UserData& ud, int start);

/**
 * @brief Calculates Julia set, writes results to ud.renderBuffer.
 *
 * @param ud user data, results are written to renderBuffer
 */
void calculateJuliaPoints(UserData& ud);

/**
 * @brief Calculates a part of the set based on the number of threads.
 *
 * @param ud user data, results are written to renderBuffer
 * @param start calculates every [number of threads] points, starting from here
 */
void calculateJuliaPointsThread(UserData& ud, int start);

}

#endif /* Mandelbrot_h */
