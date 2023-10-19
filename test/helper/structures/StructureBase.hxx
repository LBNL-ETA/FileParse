#pragma once

#include <string>
#include <optional>
#include <variant>

namespace Helper
{
    struct BaseElement
    {
        std::string text;
        int integer_number{0};
        double double_number{0.0};
        bool boolean_field{true};
        size_t size_t_field{0u};
        std::optional<bool> boolean_optional;
        std::optional<std::string> optional_text;
        std::optional<int> optional_int;
        std::optional<double> optional_double;
        std::variant<double, std::string> variant_field{0.0};
        std::optional<std::variant<std::string, int>> optional_variant{22};
    };
}