#pragma once

#include <array>
#include <string>
#include <algorithm>

namespace Helper
{
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

    constexpr std::array<std::string_view, 8> DayToString
      = {"None", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    std::string toDayString(Day day);
    Day toDay(std::string_view str);

    enum class Color
    {
        None,
        Red,
        Green,
        Blue
    };

    constexpr std::array<std::string_view, 4> ColorToString = {"None", "Red", "Green", "Blue"};
    std::string toColorString(Color color);
    Color toColor(std::string_view str);

    enum class Option
    {
        None,
        Low,
        High
    };

    constexpr std::array<std::string_view, 4> OptionToString = {"None", "Low", "High"};
    std::string toOptionString(Option option);
    Option toOption(std::string_view str);

}   // namespace Helper
