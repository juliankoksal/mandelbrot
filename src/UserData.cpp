//
//  UserData.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#include "UserData.hpp"

UserData::UserData(int precision)
{
    this->isJuliaSet = false;
    this->isDrawingFrame = false;
    this->precision = precision;
    this->zoom = 1.0;
    this->centreX = -0.75;
    this->centreY = 0.0;
    setTransforms();
}

bool UserData::getIsDrawingFrame()
{
    return isDrawingFrame;
}

bool UserData::getIsJuliaSet()
{
    return isJuliaSet;
}

std::complex<long double> UserData::getPointClicked()
{
    return pointClicked;
}

long double UserData::getScale()
{
    return scale;
}

long double UserData::getTranslateX()
{
    return translateX;
}

long double UserData::getTranslateY()
{
    return translateY;
}

long double UserData::getZoom()
{
    return zoom;
}

long double UserData::getCentreX()
{
    return centreX;
}

long double UserData::getCentreY()
{
    return centreY;
}

void UserData::setIsJuliaSet(bool value)
{
    isJuliaSet = value;
}

void UserData::setPointClicked(std::complex<long double> value)
{
    pointClicked = value;
}

void UserData::setIsDrawingFrame(bool value)
{
    isDrawingFrame = value;
}

void UserData::setZoom(long double value)
{
    zoom = value;
    setTransforms();
}

void UserData::setCentreX(long double value)
{
    centreX = value;
    setTransforms();
}

void UserData::setCentreY(long double value)
{
    centreY = value;
    setTransforms();
}

void UserData::setTransforms()
{
    scale = (2.5 / zoom) / precision;
    translateX = centreX - (scale * precision) / 2.0;
    translateY = centreY - (scale * precision) / 2.0;
}
