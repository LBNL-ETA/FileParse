#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct BaseElement
    {
        std::string text;
        int integer_number{0};
        double double_number{0.0};
        std::optional<std::string> optional_text;
        std::optional<int> optional_int;
        std::optional<double> optional_double;
    };
}   // namespace Helper