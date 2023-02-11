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
    this->viewLeft = -2.0;
    this->viewRight = 0.5;
    this->viewBottom = -1.25;
    this->viewTop = 1.25;
    this->isJuliaSet = false;
}
