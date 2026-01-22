#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct EnumElement;

    // XML functions
    [[nodiscard]] std::optional<EnumElement> loadEnumElementXML(std::string_view fileName);
    [[nodiscard]] int saveEnumElementXML(const EnumElement& element, std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<EnumElement> loadEnumElementJSON(std::string_view fileName);
    [[nodiscard]] int saveEnumElementJSON(const EnumElement& element, std::string_view fileName);
}   // namespace Helper
