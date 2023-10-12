#pragma once

#include <string>
#include <map>
#include <optional>

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
}   // namespace Helper