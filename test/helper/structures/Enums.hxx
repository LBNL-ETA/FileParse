#pragma once

#include <array>
#include <string>
#include <algorithm>

namespace Helper {
    enum class Day {
        None,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    constexpr std::array<std::string_view, 8> DayToString = {
            "None",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"
    };

    inline std::string toDayString(Day day) {
        return std::string{DayToString[static_cast<int>(day)]};
    }

    inline Day toDay(std::string_view str) {
        auto it = std::find(DayToString.begin(), DayToString.end(), str);
        if (it != DayToString.end())
            return static_cast<Day>(std::distance(DayToString.begin(), it));
        return Day::None;
    }

    enum class Color {
        None,
        Red,
        Green,
        Blue
    };

    constexpr std::array<std::string_view, 4> ColorToString = {
            "None",
            "Red",
            "Green",
            "Blue"
    };

    inline std::string toColorString(Color color) {
        return std::string{ColorToString[static_cast<int>(color)]};
    }

    inline Color toColor(std::string_view str) {
        if (auto it = std::find(ColorToString.begin(), ColorToString.end(), str);it != ColorToString.end())
            return static_cast<Color>(std::distance(ColorToString.begin(), it));
        return Color::None;
    }
}
