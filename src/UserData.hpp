//
//  UserData.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef UserData_hpp
#define UserData_hpp

#include <complex>

struct UserData
{
    double viewLeft;
    
    double viewRight;
    
    double viewBottom;
    
    double viewTop;
    
    bool isJuliaSet;
    
    std::complex<double> pointClicked;
    
    UserData();
};

#endif /* UserData_hpp */
