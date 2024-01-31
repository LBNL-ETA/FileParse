#pragma once

#include <functional>

#include "CMAValues.hxx"

namespace Helper
{
    // Example of a structure as key
    struct CMAStringOptions
    {
        std::string glazingOption;
        std::string spacerOption;

        CMAStringOptions() = default;
        CMAStringOptions(std::string glazing, std::string spacer) :
            glazingOption(std::move(glazing)), spacerOption(std::move(spacer))
        {}

        // Operator for ordering in std::map
        bool operator<(const CMAStringOptions & other) const
        {
            if(glazingOption < other.glazingOption)
                return true;
            if(glazingOption == other.glazingOption && spacerOption < other.spacerOption)
                return true;
            return false;
        }

        // Operator for equality in std::unordered_map
        bool operator==(const CMAStringOptions & other) const
        {
            return glazingOption == other.glazingOption && spacerOption == other.spacerOption;
        }
    };
}   // namespace Helper

namespace std
{
    template<>
    struct hash<Helper::CMAStringOptions>
    {
        hash() = default;                     // Default constructor
        hash(const hash & other) = default;   // Copy constructor
        ~hash() = default;                    // Destructor

        std::size_t operator()(const Helper::CMAStringOptions & k) const
        {
            return std::hash<std::string>()(k.glazingOption)
                   ^ std::hash<std::string>()(k.spacerOption);
        }
    };
}   // namespace std

namespace Helper
{
    struct CMAElement
    {
        std::unordered_map<CMAStringOptions, CMAValues> options;

        CMAElement() = default;
        CMAElement(const std::initializer_list<std::pair<CMAStringOptions, CMAValues>> & initList) :
            options(initList.begin(), initList.end())
        {}
    };
}   // namespace Helper