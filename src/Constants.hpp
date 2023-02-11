//
//  Constants.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <array>

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
 * Width and height of the window in pixels.
 */
inline constexpr int WINDOW_SIZE = 800;

/**
 * Number of points drawn in a single row/column.
 * Higher values will increase image quality at a large performance cost.
 */
inline constexpr double PRECISION = 800;

/**
 * Maximum number of iterations before a point is coloured black.
 * Higher values will increase accuracy at a very large performance cost.
 */
inline constexpr int MAX_ITERATION = 500;

/**
 * Points which diverge after less than this number of iterations will use the
 * secondary colour palette instead of the primary palette.
 */
inline constexpr int SECONDARY_COLOUR_IT_CUTOFF = 20;

/**
 * Number of iterations associated with the last colour of the secondary palette.
 * Points which diverge after this number of iterations or more will all be
 * coloured the same.
 */
inline constexpr int SECONDARY_COLOUR_MAX_IT = SECONDARY_COLOUR_IT_CUTOFF * 3;

/**
 * Proportion of the view width/height to pan by on arrow key press.
 */
inline constexpr double PAN_STEP = 0.1;

inline constexpr double PAN = PAN_STEP * PRECISION;

/**
 * Factor to zoom in/out by on x/z key press.
 */
inline constexpr double ZOOM_STEP = 1.2;

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

inline constexpr std::array<COLOUR, MAX_ITERATION> PRIMARY_COLOUR =
    []() consteval
{
    std::array<COLOUR, MAX_ITERATION> result;
    int i = 0;
    for (; i < 100 && i < MAX_ITERATION; ++i)
    {
        result[i].R = 1.0;
        result[i].G = 0.5 + (GET_BRIGHTNESS_PRIMARY(i, 0, 99) * 0.5);
        result[i].B = GET_BRIGHTNESS_PRIMARY(i, 0, 99);
    }
    for (; i < 400 && i < MAX_ITERATION; ++i)
    {
        result[i].R = 0.5 + (GET_BRIGHTNESS_PRIMARY(i, 100, 399) * 0.5);
        result[i].G = 0.0 + (GET_BRIGHTNESS_PRIMARY(i, 100, 399) * 0.5);
        result[i].B = 0.0;
    }
    for (; i < 800 && i < MAX_ITERATION; ++i)
    {
        result[i].R = 0.1 + (GET_BRIGHTNESS_PRIMARY(i, 400, 799) * 0.4);
        result[i].G = 0.0;
        result[i].B = 0.0;
    }
    for (; i < MAX_ITERATION; ++i)
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
    double proportion = i / SECONDARY_COLOUR_MAX_IT;
    if (i > SECONDARY_COLOUR_MAX_IT)
    {
        proportion = 1.0;
    }
    return 1.0 - proportion;
}

inline constexpr std::array<COLOUR, MAX_ITERATION> SECONDARY_COLOUR =
    []() consteval
{
    std::array<COLOUR, MAX_ITERATION> result;
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        result[i].R = 1.0 - GET_BRIGHTNESS_SECONDARY(i);
        result[i].G = 1.0 - GET_BRIGHTNESS_SECONDARY(i);
        result[i].B = 1.0 - GET_BRIGHTNESS_SECONDARY(i) * 0.7;
    }
    return result;
}();

#endif /* Constants_hpp */
