//
//  UserData.cpp
//  Mandelbrot
//
//  Created by Julian Koksal on 2023-02-05.
//

#include "UserData.hpp"

UserData::UserData()
{
    loadDefaultValues();
}

void UserData::loadDefaultValues()
{
    this->scaleFactor = 0.003125;
    this->translateX = -2.0;
    this->translateY = -1.25;
    this->isJuliaSet = false;
}
