#pragma once

#include <set>
#include <optional>

namespace Helper
{
    struct SetElementDouble
    {
        std::set<double> values;
    };

    struct SetElementOptionalDouble
    {
        std::optional<std::set<double>> values;
    };
}