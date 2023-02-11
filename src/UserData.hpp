//
//  UserData.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef UserData_hpp
#define UserData_hpp

#include <complex>

/**
 * @brief Represents the current state of the program.
 */
struct UserData
{
    double scaleFactor;
    
    double translateX;
    
    double translateY;
    
    bool allPointsMaxIterations;
    
    double allPointsMaxIterationsScaleFactor;
    
    /**
     * @brief True if a Julia set is currently displayed, false if Mandelbrot.
     */
    bool isJuliaSet;
    
    /**
     * @brief Last point that was clicked by the user.
     */
    std::complex<double> pointClicked;
    
    /**
     * @brief Constructor. Loads default values.
     */
    UserData();
    
    /**
     * @brief Sets member variables to their default values.
     *
     * Default viewing volume is x from -2.0 to 0.5, y from -1.25 to 1.25.
     */
    void loadDefaultValues();
};

#endif /* UserData_hpp */
