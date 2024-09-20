#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct EnumElement;

    [[nodiscard]] std::optional<EnumElement> loadEnumElement(std::string_view fileName);
    [[nodiscard]] int saveEnumElement(const EnumElement& element, std::string_view fileName);
}