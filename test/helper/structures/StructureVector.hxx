#pragma once

#include <vector>
#include <optional>

namespace Helper
{
    struct VectorElement
    {
        std::vector<double> values;
    };

    struct OptionalVectorElement
    {
        std::optional<std::vector<double>> values;
    };
}   // namespace Helper