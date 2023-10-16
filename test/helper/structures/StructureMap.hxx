#pragma once

#include <string>
#include <map>
#include <optional>

#include "Enums.hxx"

namespace Helper
{
    struct MapElementString
    {
        std::map<std::string, std::string> ordered;
        std::unordered_map<std::string, std::string> unordered;
    };

    struct MapElementDouble
    {
        std::map<std::string, double> values;
    };

    struct MapElementOptionalString
    {
        std::optional<std::map<std::string, std::string>> values;
    };

    struct MapElementEnum
    {
        std::map<Helper::Day, std::string> days;
    };

    struct MapElementEnumDouble
    {
        std::map<Helper::Day, double> days;
    };
}   // namespace Helper