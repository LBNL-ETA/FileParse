#pragma once

#include <string>

namespace Helper
{
    struct SetElementDouble;
    struct SetElementOptionalDouble;
    struct SetElementEnum;

    std::string testSetElementDoubleDatabase();
    std::string setElementDouble();

    std::string testSetElementEmptyDatabase();
    std::string setElementEmpty();

    std::string testSetElementOptionalDoubleDatabase();
    std::string setElementOptionalDouble();

    std::string testSetElementEnumDatabase();
    std::string setElementEnum();

    SetElementDouble loadSetElementDouble(std::string_view fileName);
    void saveSetElementDouble(const SetElementDouble & element, std::string_view fileName);

    SetElementOptionalDouble loadSetElementOptionalDouble(std::string_view fileName);
    void saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                      std::string_view fileName);

    SetElementEnum loadSetElementEnum(std::string_view fileName);
    void saveSetElementEnum(const SetElementEnum & element, std::string_view fileName);
}   // namespace Helper