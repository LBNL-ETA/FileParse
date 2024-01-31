#pragma once

#include <string>

namespace Helper
{
    struct BaseElement;

    [[nodiscard]] std::string testBaseElementDatabase();
    [[nodiscard]] std::string baseElement();

    [[nodiscard]] BaseElement loadBaseElement(std::string_view fileName);
    [[nodiscard]] int saveBaseElement(const BaseElement & base, std::string_view fileName);
}