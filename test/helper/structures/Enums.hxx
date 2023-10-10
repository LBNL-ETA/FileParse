#pragma once

#include <unordered_map>
#include <string>

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

    const std::unordered_map<Day, std::string> DayToString{{Day::Monday, "Monday"},
                                                           {Day::Tuesday, "Tuesday"},
                                                           {Day::Wednesday, "Wednesday"},
                                                           {Day::Thursday, "Thursday"},
                                                           {Day::Friday, "Friday"},
                                                           {Day::Saturday, "Saturday"},
                                                           {Day::Sunday, "Sunday"}};

    const std::unordered_map<std::string, Day> StringToDay = []() {
        std::unordered_map<std::string, Day> map;
        for(const auto & [key, value] : DayToString)
            map[value] = key;
        return map;
    }();

    inline std::string toDayString(Day day)
    {
        if(DayToString.count(day) == 0)
            return "";
        return DayToString.at(day);
    }

    inline Day toDay(std::string_view str)
    {
        if(StringToDay.count(str.data()) == 0)
            return Day::None;
        return StringToDay.at(str.data());
    }

    enum class Color
    {
        None,
        Red,
        Green,
        Blue
    };

    const std::unordered_map<Color, std::string> ColorToString{
      {Color::Red, "Red"}, {Color::Green, "Green"}, {Color::Blue, "Blue"}};

    const std::unordered_map<std::string, Color> StringToColor = []() {
        std::unordered_map<std::string, Color> map;
        for(const auto & [key, value] : ColorToString)
            map[value] = key;
        return map;
    }();

    inline std::string toColorString(Color color)
    {
        if(ColorToString.count(color) == 0)
            return "";
        return ColorToString.at(color);
    }

    inline Color toColor(std::string_view str)
    {
        if(StringToColor.count(str.data()) == 0)
            return Color::None;
        return StringToColor.at(str.data());
    }
}