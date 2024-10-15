/// File: StringConversion.hxx
/// @brief Provides functionality to convert strings to various basic data types
///        in the FileParse namespace.

#pragma once

#include <string>
#include <array>
#include <map>
#include <algorithm>

namespace FileParse
{
    /// Converts a string to a specified data type.
    /// @tparam T The data type to convert the string to.
    /// @param str The string to be converted.
    /// @return The converted value of type T.
    template<typename T>
    inline T from_string(const std::string & str);

    /// Specialization of from_string for int.
    /// @param str The string to be converted to int.
    /// @return The converted int value.
    template<>
    inline int from_string<int>(const std::string & str)
    {
        return std::stoi(str);
    }

    /// Specialization of from_string for double.
    /// @param str The string to be converted to double.
    /// @return The converted double value.
    template<>
    inline double from_string<double>(const std::string & str)
    {
        return std::stod(str);
    }

    /// Specialization of from_string for size_t.
    /// @param str The string to be converted to size_t.
    /// @return The converted size_t value.
    template<>
    inline size_t from_string<size_t>(const std::string & str)
    {
        return std::stoul(str);
    }

    /// Specialization of from_string for std::string.
    /// @param str The string to be returned.
    /// @return The input string itself.
    template<>
    inline std::string from_string<std::string>(const std::string & str)
    {
        return str;
    }

    /// Helper function to invoke from_string with the appropriate specialization.
    /// @tparam T The data type to convert the string to.
    /// @param str The string to be converted.
    /// @return The converted value of type T.
    template<typename T>
    T from_string_helper(const std::string & str)
    {
        return from_string<T>(str);
    }

    /// Enumerator to string conversion routines.

    /// Converts an enumerator value to a string.
    /// @tparam EnumType The type of the enumerator.
    /// @tparam N The number of enumerator values.
    /// @param value The enumerator value to convert to a string.
    /// @param values An array of strings representing the enumerator values.
    /// @return The string representation of the enumerator value.
    template<typename EnumType, std::size_t N>
    EnumType enumFromString(std::string_view name,
                            const std::array<std::string, N> & values,
                            EnumType defaultValue)
    {
        for(std::size_t i = 0; i < values.size(); ++i)
        {
            if(values[i] == name)
            {
                return static_cast<EnumType>(i);
            }
        }
        return defaultValue;
    }

    /// Converts an enumerator value to a string.
    /// @tparam EnumType The type of the enumerator.
    /// @tparam N The number of enumerator values.
    /// @param value The enumerator value to convert to a string.
    /// @param values An array of strings representing the enumerator values.
    /// @return The string representation of the enumerator value.
    template<typename EnumType, std::size_t N>
    std::string enumToString(EnumType value, const std::array<std::string, N> & values)
    {
        const auto index{static_cast<std::size_t>(value)};
        if(index < values.size())
        {
            return values[index];
        }
        return "Unknown";
    }

    /// Converts an enumerator value to a string.
    /// @tparam T The type of the enumerator.
    /// @param enumType The enumerator value to convert to a string.
    /// @param enumMap A map of enumerator values to string representations.
    /// @return The string representation of the enumerator value.
    template<typename T>
    std::string enumToString(const T enumType, const std::map<T, std::string> & enumMap)
    {
        if(enumMap.count(enumType) > 0)
        {
            return enumMap.at(enumType);
        }
        return "Unknown";
    }

    /// Converts a string to an enumerator value.
    /// @tparam T The type of the enumerator.
    /// @param enumString The string to convert to an enumerator value.
    /// @param enumMap A map of enumerator values to string representations.
    /// @return The enumerator value corresponding to the input string.
    template<typename T>
    T enumFromString(std::string_view enumString, const std::map<T, std::string> & enumMap)
    {
        if(!enumString.empty())
        {
            auto it
              = std::find_if(enumMap.begin(), enumMap.end(), [&enumString](const auto & pair) {
                    return pair.second == enumString;
                });

            if(it != enumMap.end())
            {
                return it->first;
            }
        }

        return enumMap.begin()->first;
    }
}   // namespace FileParse