#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct AttributesTest;

    // XML functions
    [[nodiscard]] std::optional<AttributesTest> loadAttributesElementXML(std::string_view fileName);
    [[nodiscard]] int saveAttributesElementXML(const AttributesTest & object, std::string_view fileName);
}   // namespace Helper
