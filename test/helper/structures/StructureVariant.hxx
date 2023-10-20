#pragma once

#include <string>
#include <variant>
#include <vector>
#include <optional>

namespace Helper
{
    struct ElementTemperature
    {
        double temperature{0};
    };

    struct ElementHumidity
    {
        std::string humidity;
    };

    // This is example when the entire tag structure is loaded
    // and then part of the object are determined to be a variant.
    struct VariantParent
    {
        std::string name;
        std::variant<ElementTemperature, ElementHumidity> value;
        std::optional<std::string> optionalString;
    };

    // All variations of the above structure should be stored here
    struct VariantsAll
    {
        std::vector<VariantParent> values;
    };
}