#pragma once

#include <string>
#include <optional>
#include <variant>
#include <vector>

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
        std::variant<double, std::string> variant_field{0.0};
    };

    struct VectorElement
    {
        std::vector<double> values;
    };
}   // namespace Helper