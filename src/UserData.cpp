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
    this->renderBuffer =  std::array<std::array<int, PRECISION>, PRECISION>();
    this->scaleFactor = 2.5 / PRECISION;
    this->translateX = -2.0;
    this->translateY = -1.25;
}
