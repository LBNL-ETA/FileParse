#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct EnumElement;

    [[nodiscard]] std::optional<EnumElement> loadEnumElementJSON(std::string_view fileName);
    [[nodiscard]] int saveEnumElementJSON(const EnumElement& element, std::string_view fileName);
}
