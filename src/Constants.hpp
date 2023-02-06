//
//  Constants.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <array>

constexpr int WINDOW_SIZE = 800;

constexpr double PRECISION = 800;

constexpr int MAX_ITERATION = 500;

constexpr int PRIMARY_BRIGHTNESS_EXP = 10;

constexpr int SECONDARY_BRIGHTNESS_EXP = 15;

constexpr int SECONDARY_COLOUR_ITERATION_CUTOFF = 20;

constexpr double PAN_STEP = 0.1;

constexpr double ZOOM_STEP = 1.2;

constexpr double POW(double base, int exponent)
{
    double result = 1.0;
    for (int i = 0; i < exponent; ++i)
    {
        result *= base;
    }
    return result;
};

constinit std::array<double, MAX_ITERATION> G_PRIMARY = []() {
    std::array<double, MAX_ITERATION> result{};
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        double proportion = i < 1000.0 ? (double)i / 1000.0 : 1.0;
        double brightness = POW(1.0 - proportion, PRIMARY_BRIGHTNESS_EXP);
        result[i] = 0.5 + (brightness * 0.5);
    }
    return result;
}();

constinit std::array<double, MAX_ITERATION> B_PRIMARY = []() {
    std::array<double, MAX_ITERATION> result{};
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        double proportion = i < 1000.0 ? (double)i / 1000.0 : 1.0;
        double brightness = POW(1.0 - proportion, PRIMARY_BRIGHTNESS_EXP);
        result[i] = brightness;
    }
    return result;
}();

constinit std::array<double, MAX_ITERATION> R_SECONDARY = []() {
    std::array<double, MAX_ITERATION> result{};
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        double proportion = i < 1000.0 ? (double)i / 1000.0 : 1.0;
        double brightness = POW(1.0 - proportion, SECONDARY_BRIGHTNESS_EXP);
        result[i] = 1.0 - brightness;
    }
    return result;
}();

constinit std::array<double, MAX_ITERATION> G_SECONDARY = []() {
    std::array<double, MAX_ITERATION> result{};
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        double proportion = i < 1000.0 ? (double)i / 1000.0 : 1.0;
        double brightness = POW(1.0 - proportion, SECONDARY_BRIGHTNESS_EXP);
        result[i] = 1.0 - brightness;
    }
    return result;
}();

constinit std::array<double, MAX_ITERATION> B_SECONDARY = []() {
    std::array<double, MAX_ITERATION> result{};
    for (int i = 0; i < MAX_ITERATION; ++i)
    {
        double proportion = i < 1000.0 ? (double)i / 1000.0 : 1.0;
        double brightness = POW(1.0 - proportion, SECONDARY_BRIGHTNESS_EXP);
        result[i] = 1.0 - brightness * 0.7;
    }
    return result;
}();

#endif /* Constants_hpp */
