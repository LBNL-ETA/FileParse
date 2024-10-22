#pragma once

#include <string>

namespace FileParse
{
    extern std::string formatDouble(double value,
                                    int precision,
                                    double scientificLowerBound = 0.001,
                                    double scientificUpperBound = 100000);
}