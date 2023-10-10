#pragma once

#include <string>
#include <unordered_map>
#include <optional>

#include "Enums.hxx"

namespace Helper
{
    struct EnumElement
    {
        Day day{Day::None};
        std::optional<Color> color;
    };
}   // namespace FileParse