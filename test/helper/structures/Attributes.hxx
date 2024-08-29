#pragma once

#include <string>

#include "Enums.hxx"

namespace Helper
{
    struct AttributesTest
    {
        std::string name;
        int age{0};
        double height{0.0};
        Day day{Day::None};
    };
}