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
    };
}