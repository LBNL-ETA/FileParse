#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <optional>
#include <utility>

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

    // Structure to be used in map as value
    struct CMAValues
    {
        double conductivity{0};
        double filmCoefficient{0};

        CMAValues() = default;
        CMAValues(double conductivity, double film) :
            conductivity(conductivity), filmCoefficient(film)
        {}

        // Equality operator
        bool operator==(const CMAValues& other) const
        {
            return conductivity == other.conductivity &&
                   filmCoefficient == other.filmCoefficient;
        }
    };

    // Example of a structure as key
    struct CMAOptions
    {
        std::string glazingOption;
        std::string spacerOption;

        CMAOptions() = default;
        CMAOptions(std::string glazing, std::string spacer) :
            glazingOption(std::move(glazing)), spacerOption(std::move(spacer))
        {}

        // Operator for ordering in std::map
        bool operator<(const CMAOptions & other) const
        {
            if(glazingOption < other.glazingOption)
                return true;
            if(glazingOption == other.glazingOption && spacerOption < other.spacerOption)
                return true;
            return false;
        }

        // Operator for equality in std::unordered_map
        bool operator==(const CMAOptions & other) const
        {
            return glazingOption == other.glazingOption && spacerOption == other.spacerOption;
        }
    };
}   // namespace Helper

namespace std
{
    template<>
    struct hash<Helper::CMAOptions>
    {
        hash() = default; // Default constructor
        hash(const hash& other) = default; // Copy constructor
        ~hash() = default; // Destructor

        std::size_t operator()(const Helper::CMAOptions & k) const
        {
            return std::hash<std::string>()(k.glazingOption)
                   ^ std::hash<std::string>()(k.spacerOption);
        }
    };
}

namespace Helper
{
    struct CMAElement
    {
        std::unordered_map<CMAOptions, CMAValues> options;

        CMAElement() = default;
        CMAElement(const std::initializer_list<std::pair<CMAOptions, CMAValues>> & initList) :
            options(initList.begin(), initList.end())
        {}
    };
}