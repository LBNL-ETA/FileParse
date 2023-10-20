#pragma once

#include <string>
#include <variant>
#include <vector>

namespace Helper
{
    // This is example when the entire tag structure is loaded
    // and then part of the object are determined to be a variant.
    struct VariantParent
    {
        std::string name;
        std::variant<std::string, double> value;
    };

    // All variations of the above structure should be stored here
    struct VariantsAll
    {
        std::vector<VariantParent> values;
    };
}