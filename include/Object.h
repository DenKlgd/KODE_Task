#pragma once

#include <string>
#include <time.h>
#include <algorithm>


struct Object
{
    std::string _name = "";
    double _x = 0;
    double _y = 0;
    std::string _type = "";
    time_t _time = time(0);
};

bool checkString(const std::string& str);
bool checkIfFloat(const std::string& str);
