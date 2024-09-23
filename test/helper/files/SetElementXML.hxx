#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct SetElementDouble;
    struct SetElementOptionalDouble;
    struct SetElementEnum;

    [[nodiscard]] std::string testSetElementEmptyDatabase();
    [[nodiscard]] std::string setElementEmpty();

    [[nodiscard]] std::string testSetElementOptionalDoubleDatabase();
    [[nodiscard]] std::string setElementOptionalDouble();

    [[nodiscard]] std::string testSetElementEnumDatabase();
    [[nodiscard]] std::string setElementEnum();

    [[nodiscard]] std::optional<SetElementDouble> loadSetElementDouble(std::string_view fileName);
    [[nodiscard]] int saveSetElementDouble(const SetElementDouble & element,
                                           std::string_view fileName);

    [[nodiscard]] SetElementOptionalDouble loadSetElementOptionalDouble(std::string_view fileName);
    [[nodiscard]] int saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                      std::string_view fileName);

    [[nodiscard]] SetElementEnum loadSetElementEnum(std::string_view fileName);
    [[nodiscard]] int saveSetElementEnum(const SetElementEnum & element, std::string_view fileName);
}   // namespace Helper