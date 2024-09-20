#pragma once

#include <string>

namespace Helper
{
    struct AttributesTest;

    [[nodiscard]] AttributesTest loadAttributesElement(std::string_view fileName);
    [[nodiscard]] int saveAttributesElement(const AttributesTest & object, std::string_view fileName);
}