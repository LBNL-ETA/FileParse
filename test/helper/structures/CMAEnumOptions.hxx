#pragma once

#include <functional>

#include "CMAValues.hxx"
#include "Enums.hxx"

namespace Helper
{
    struct CMAEnumOptions
    {
        Option glazingOption{Option::Low};
        Option spacerOption{Option::Low};

        CMAEnumOptions() = default;
        CMAEnumOptions(Option glazing, Option spacer) : glazingOption(glazing), spacerOption(spacer)
        {}

        // Operator for ordering in std::map
        bool operator<(const CMAEnumOptions & other) const
        {
            if(glazingOption < other.glazingOption)
                return true;
            if(glazingOption == other.glazingOption && spacerOption < other.spacerOption)
                return true;
            return false;
        }

        bool operator==(const CMAEnumOptions & other) const
        {
            return glazingOption == other.glazingOption && spacerOption == other.spacerOption;
        }
    };
}   // namespace Helper

namespace std
{
    template<>
    struct hash<Helper::CMAEnumOptions>
    {
        hash() = default;                     // Default constructor
        hash(const hash & other) = default;   // Copy constructor
        ~hash() = default;                    // Destructor

        std::size_t operator()(const Helper::CMAEnumOptions & k) const
        {
            return std::hash<Helper::Option>()(k.glazingOption)
                   ^ std::hash<Helper::Option>()(k.spacerOption);
        }
    };
}   // namespace std