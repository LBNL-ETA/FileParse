/// File: FP_StringConversion.hxx
/// @brief Provides functionality to convert strings to various basic data types
///        in the FileParse namespace.

#pragma once

#include <string>

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
}   // namespace FileParse