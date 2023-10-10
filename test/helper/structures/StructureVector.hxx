#pragma once

#include <vector>
#include <optional>

#include "Enums.hxx"

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

    struct EnumVectorElement
    {
        std::vector<Day> days;
    };
}   // namespace Helper