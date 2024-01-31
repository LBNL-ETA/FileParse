#include "Enums.hxx"

#include <ostream>

namespace Helper
{
    std::string toDayString(Day day)
    {
        return std::string{DayToString[static_cast<int>(day)]};
    }

    Day toDay(std::string_view str)
    {
        if(auto it = std::find(DayToString.begin(), DayToString.end(), str);
           it != DayToString.end())
            return static_cast<Day>(std::distance(DayToString.begin(), it));
        return Day::None;
    }

    std::string toColorString(Color color)
    {
        return std::string{ColorToString[static_cast<int>(color)]};
    }

    Color toColor(std::string_view str)
    {
        if(auto it = std::find(ColorToString.begin(), ColorToString.end(), str);
           it != ColorToString.end())
            return static_cast<Color>(std::distance(ColorToString.begin(), it));
        return Color::None;
    }

    std::string toOptionString(Option option)
    {
        return std::string{OptionToString[static_cast<int>(option)]};
    }

    Option toOption(std::string_view str)
    {
        if(auto it = std::find(OptionToString.begin(), OptionToString.end(), str);
           it != OptionToString.end())
            return static_cast<Option>(std::distance(OptionToString.begin(), it));
        return Option::None;
    }
}   // namespace Helper
