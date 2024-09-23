#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct AttributesTest;

    [[nodiscard]] std::optional<AttributesTest> loadAttributesElement(std::string_view fileName);
    [[nodiscard]] int saveAttributesElement(const AttributesTest & object, std::string_view fileName);
}