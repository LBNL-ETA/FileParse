#pragma once

#include <string>
#include <optional>

#include "Enums.hxx"

namespace Helper
{
    struct AttributesTest
    {
        std::string name;
        int age{0};
        double height{0.0};
        Day day{Day::None};
        std::optional<int> optional_age;
        std::optional<std::string> nickname; // string is handled by different functions. Need this for coverage.
        std::optional<Color> color{Color::None};
    };
}