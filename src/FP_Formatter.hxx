#pragma once

#include <sstream>

namespace FileParse
{
    extern void formatDouble(std::ostringstream & oss,
                             double value,
                             int precision,
                             double scientificLowerBound = 0.001,
                             double scientificUpperBound = 100000);
}