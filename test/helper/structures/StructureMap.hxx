#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <optional>
#include <utility>

#include "Enums.hxx"

namespace Helper
{
    //! \brief This structure is used in case where map items are stored in a way where
    //!    the key string used as tag value in the structure while the value is stored
    //!    as the value for the given tag.
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