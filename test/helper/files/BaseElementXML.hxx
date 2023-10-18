#pragma once

#include <string>

namespace Helper
{
    struct BaseElement;

    std::string testBaseElementDatabase();
    std::string baseElement();

    BaseElement loadBaseElement(std::string_view fileName);
    void saveBaseElement(const BaseElement & base, std::string_view fileName);
}