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

    //// This is needed by GTest so it can be compared with EXPECT_EQ
    //inline std::ostream& operator<<(std::ostream& os, Day day) {
    //    switch (day) {
    //        case Day::None:     return os << "None";
    //        case Day::Monday:   return os << "Monday";
    //        case Day::Tuesday:  return os << "Tuesday";
    //        case Day::Wednesday:return os << "Wednesday";
    //        case Day::Thursday: return os << "Thursday";
    //        case Day::Friday:   return os << "Friday";
    //        case Day::Saturday: return os << "Saturday";
    //        case Day::Sunday:   return os << "Sunday";
    //        default:            return os << "Unknown Day";
    //    }
    //}

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

    std::ostream& operator<<(std::ostream& os, const Color& color);
}   // namespace Helper
