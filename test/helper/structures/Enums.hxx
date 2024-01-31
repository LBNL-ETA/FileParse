// File: Enums.hxx
// Brief: Declarations for helper namespace, including enums and conversion functions.

#pragma once

#include <array>
#include <string>
#include <algorithm>

namespace Helper
{
    /// Enum Day - Represents days of the week.
    enum class Day
    {
        None,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    /// Maps Day enum values to their string representations.
    constexpr std::array<std::string_view, 8> DayToString
      = {"None", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    /// Converts a Day enum to its string representation.
    /// @param day The Day enum to convert.
    /// @return A string representing the given day.
    std::string toDayString(Day day);

    /// Converts a string to its corresponding Day enum value. In case string is not recognized, it
    /// will return Day::None
    /// @param str The string to convert.
    /// @return The Day enum corresponding to the given string.
    Day toDay(std::string_view str);

    /// Enum Color - Represents basic color options.
    enum class Color
    {
        None,    ///< Represents no specific color.
        Red,     ///< Represents the color Red.
        Green,   ///< Represents the color Green.
        Blue     ///< Represents the color Blue.
    };

    /// Maps Color enum values to their string representations.
    constexpr std::array<std::string_view, 4> ColorToString = {"None", "Red", "Green", "Blue"};

    /// Converts a Color enum to its string representation.
    /// @param color The Color enum to convert.
    /// @return A string representing the given color.
    std::string toColorString(Color color);

    /// Converts a string to its corresponding Color enum value. In case the string is not
    /// recognized, it will return Color::None.
    /// @param str The string to convert.
    /// @return The Color enum corresponding to the given string.
    Color toColor(std::string_view str);

    /// Enum Option - Represents options with a low, high, or none state.
    enum class Option
    {
        None,   ///< Represents no specific option or an unrecognized option.
        Low,    ///< Represents the Low option.
        High    ///< Represents the High option.
    };

    /// Maps Option enum values to their string representations.
    constexpr std::array<std::string_view, 3> OptionToString = {"None", "Low", "High"};

    /// Converts an Option enum to its string representation.
    /// @param option The Option enum to convert.
    /// @return A string representing the given option.
    std::string toOptionString(Option option);

    /// Converts a string to its corresponding Option enum value. In case the string is not
    /// recognized, it will return Option::None.
    /// @param str The string to convert.
    /// @return The Option enum corresponding to the given string.
    Option toOption(std::string_view str);


}   // namespace Helper
