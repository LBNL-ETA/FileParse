#pragma once

#include <string>

namespace Helper
{
    struct EnumElement;

    std::string testEnumDatabase();
    std::string enumElement();

    std::string testEnumDatabaseOptionalMissing();
    std::string enumElementOptionalMissing();

    EnumElement loadEnumElement(std::string_view fileName);
    void saveEnumElement(const EnumElement& element, std::string_view fileName);
}