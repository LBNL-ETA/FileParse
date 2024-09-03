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
        bool boolean_field{true};
        size_t size_t_field{0u};
        std::optional<bool> boolean_optional;
        std::optional<std::string> optional_text;
        std::optional<int> optional_int;
        std::optional<double> optional_double;
        std::variant<double, std::string> variant_field{0.0};
        std::optional<std::variant<std::string, int>> optional_variant{22};
    };

    struct TextElement
    {
        std::string text;
    };

    struct IntegerNumberElement
    {
        int integer_number{0};
    };

    struct DoubleNumberElement
    {
        double double_number{0.0};
    };

    struct BooleanFieldElement
    {
        bool boolean_field{true};
    };

    struct SizeTFieldElement
    {
        size_t size_t_field{0u};
    };

    struct OptionalBooleanElement
    {
        std::optional<bool> optional_boolean;
    };

    struct OptionalTextElement
    {
        std::optional<std::string> optional_text;
    };

    struct OptionalIntegerElement
    {
        std::optional<int> optional_int;
    };

    struct OptionalDoubleElement
    {
        std::optional<double> optional_double;
    };

    struct OptionalSizeTFieldElement
    {
        std::optional<size_t> optional_size_t_field;
    };

    struct VariantFieldElement
    {
        std::variant<double, std::string> variant_field{0.0};
    };

    struct OptionalVariantElement
    {
        std::optional<std::variant<std::string, int>> optional_variant;
    };

    struct OptionalVariantVectorElement
    {
        std::optional<std::variant<std::vector<std::string>, std::vector<int>>> optional_variant_vector;
    };

}   // namespace Helper