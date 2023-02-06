//
//  UserData.hpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#ifndef UserData_hpp
#define UserData_hpp

#include <complex>

class UserData
{
public:
    UserData(int precision);
    
    bool getIsJuliaSet();
    
    std::complex<long double> getPointClicked();
    
    bool getIsDrawingFrame();
    
    long double getScale();
    
    long double getTranslateX();
    
    long double getTranslateY();
    
    long double getZoom();
    
    long double getCentreX();
    
    long double getCentreY();
    
    void setIsJuliaSet(bool value = true);
    
    void setPointClicked(std::complex<long double> value);
    
    void setIsDrawingFrame(bool value = true);
    
    void setZoom(long double value);
    
    void setCentreX(long double value);
    
    void setCentreY(long double value);
private:
    bool isJuliaSet;
    
    std::complex<long double> pointClicked;
    
    bool isDrawingFrame;
    
    int precision;
    
    long double zoom;
    
    long double centreX;
    
    long double centreY;
    
    long double scale;
    
    long double translateX;
    
    long double translateY;
    
    void setTransforms();
};

#endif /* UserData_hpp */
