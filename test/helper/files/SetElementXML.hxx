#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct SetElementDouble;
    struct SetElementOptionalDouble;
    struct SetElementEnum;

    [[nodiscard]] std::optional<SetElementDouble> loadSetElementDouble(std::string_view fileName);
    [[nodiscard]] int saveSetElementDouble(const SetElementDouble & element,
                                           std::string_view fileName);

    [[nodiscard]] std::optional<SetElementOptionalDouble>
      loadSetElementOptionalDouble(std::string_view fileName);
    [[nodiscard]] int saveSetElementOptionalDouble(const SetElementOptionalDouble & element,
                                                   std::string_view fileName);

    [[nodiscard]] std::optional<SetElementEnum> loadSetElementEnum(std::string_view fileName);
    [[nodiscard]] int saveSetElementEnum(const SetElementEnum & element, std::string_view fileName);
}   // namespace Helper