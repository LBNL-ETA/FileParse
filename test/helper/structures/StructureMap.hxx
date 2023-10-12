#pragma once

#include <string>
#include <map>
#include <optional>

#include "Enums.hxx"

namespace Helper
{
    struct MapElementString
    {
        std::map<std::string, std::string> values;
    };

    struct MapElementOptionalString
    {
        std::optional<std::map<std::string, std::string>> values;
    };

    struct MapElementEnum
    {
        std::map<Helper::Day, std::string> days;
    };
}   // namespace Helper