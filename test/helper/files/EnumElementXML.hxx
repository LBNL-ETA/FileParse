#pragma once

#include <string>

namespace Helper
{
    struct EnumElement;

    [[nodiscard]] std::string testEnumDatabase();
    [[nodiscard]] std::string enumElement();

    [[nodiscard]] std::string testEnumDatabaseOptionalMissing();
    [[nodiscard]] std::string enumElementOptionalMissing();

    [[nodiscard]] EnumElement loadEnumElement(std::string_view fileName);
    [[nodiscard]] int saveEnumElement(const EnumElement& element, std::string_view fileName);
}