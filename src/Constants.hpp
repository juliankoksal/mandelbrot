//
//  Constants.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <array>

/*
 * Configuration
 */

/**
 * Width and height of the window in pixels.
 */
inline constexpr int WINDOW_SIZE = 800;

/**
 * Number of points drawn in a single row/column.
 * Higher values will increase image quality at a very large performance cost.
 */
inline constexpr int PRECISION = 800;

/**
 * Maximum number of iterations before a point is coloured black.
 * Higher values will increase accuracy at a large performance cost.
 */
inline constexpr int MAX_ITERATIONS = 1000;

/**
 * Number of threads to use for calculating the set.
 * Higher values up to the number of CPU cores will greatly increase
 * performance.
 */
inline constexpr int NUM_THREADS = 8;

/**
 * Number of sample points for multi-sampling anti-aliasing.
 * Higher values increase quality at a small performance cost.
 */
inline constexpr int MSAA = 4;

/**
 * Proportion of the view width/height to pan by on arrow key press.
 */
inline constexpr double PAN_STEP = 0.1;

/**
 * Factor to zoom in/out by on x/z key press.
 */
inline constexpr double ZOOM_STEP = 1.2;

/**
 * Points which diverge after less than this number of iterations will use the
 * secondary colour palette instead of the primary palette.
 */
inline constexpr int SECONDARY_COLOUR_IT_CUTOFF = 20;


/*
 * Derived constants
 */

/**
 * Number of points to pan by.
 */
inline constexpr double PAN = PAN_STEP * PRECISION;

/**
 * Factor to convert window coordinates to world coordinates.
 */
inline constexpr double WINDOW_COORD_FACTOR = (double)PRECISION / (double)WINDOW_SIZE;


/*
 * Colour palettes
 */

/**
 * @brief Constant initialized RGBA colour.
 */
struct COLOUR
{
    double R;
    double G;
    double B;
    double A;
    consteval COLOUR(const double R = 1.0, const double G = 1.0,
                     const double B = 1.0, const double A = 1.0)
        : R(R), G(G), B(B), A(A)
    {
    }
};

/**
 * @brief Calculates the primary colour brightness factor.
 *
 * @param i number of iterations
 *
 * @return brightness factor from 0.0 to 1.0
 */
inline consteval double GET_BRIGHTNESS_PRIMARY(const int i, const int iMin,
                                               const int iMax)
{
    double proportion = ((double)i - (double)iMin) / (iMax - iMin);
    return 1.0 - proportion;
}

/**
 * Primary colour palette.
 */
inline constexpr std::array<COLOUR, MAX_ITERATIONS> PRIMARY_COLOUR =
    []() consteval
{
    std::array<COLOUR, MAX_ITERATIONS> result;
    int i = SECONDARY_COLOUR_IT_CUTOFF;
    // White to yellow
    for (; i < 50 && i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 1.0;
        result[i].G = 1.0;
        result[i].B = GET_BRIGHTNESS_PRIMARY(i, SECONDARY_COLOUR_IT_CUTOFF, 49);
    }
    // Yellow to orange
    for (; i < 150 && i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 1.0;
        result[i].G = 0.5 + (GET_BRIGHTNESS_PRIMARY(i, 50, 149) * 0.5);
        result[i].B = 0.0;
    }
    // Orange to red
    for (; i < 400 && i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 0.5 + (GET_BRIGHTNESS_PRIMARY(i, 150, 399) * 0.5);
        result[i].G = 0.0 + (GET_BRIGHTNESS_PRIMARY(i, 150, 399) * 0.5);
        result[i].B = 0.0;
    }
    // Red to very dark red
    for (; i < 800 && i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 0.1 + (GET_BRIGHTNESS_PRIMARY(i, 400, 799) * 0.4);
        result[i].G = 0.0;
        result[i].B = 0.0;
    }
    // Very dark red
    for (; i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 0.1;
        result[i].G = 0.0;
        result[i].B = 0.0;
    }
    return result;
}();

/**
 * @brief Calculates the secondary colour brightness factor.
 *
 * @param i number of iterations
 *
 * @return brightness factor from 0.0 to 1.0
 */
inline consteval double GET_BRIGHTNESS_SECONDARY(const double i)
{
    double proportion = i / SECONDARY_COLOUR_IT_CUTOFF;
    if (i > SECONDARY_COLOUR_IT_CUTOFF)
    {
        proportion = 1.0;
    }
    return 1.0 - proportion;
}

/**
 * Secondary colour palette.
 */
inline constexpr std::array<COLOUR, MAX_ITERATIONS> SECONDARY_COLOUR =
    []() consteval
{
    std::array<COLOUR, MAX_ITERATIONS> result;
    for (int i = 0; i < MAX_ITERATIONS; ++i)
    {
        result[i].R = 0.8 - GET_BRIGHTNESS_SECONDARY(i);
        result[i].G = 0.9 - GET_BRIGHTNESS_SECONDARY(i);
        result[i].B = 1.0 - GET_BRIGHTNESS_SECONDARY(i) * 0.7;
    }
    return result;
}();

#endif /* Constants_hpp */
