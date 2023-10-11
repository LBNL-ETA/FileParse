#pragma once

#include <set>
#include <optional>

#include "Enums.hxx"

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

    struct SetElementEnum
    {
        std::set<Day> days;
    };
}