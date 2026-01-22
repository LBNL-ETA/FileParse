#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct SetElementDouble;
    struct SetElementOptionalDouble;
    struct SetElementEnum;

    [[nodiscard]] std::optional<SetElementDouble> loadSetElementDoubleJSON(std::string_view fileName);
    [[nodiscard]] int saveSetElementDoubleJSON(const SetElementDouble & element,
                                               std::string_view fileName);

    [[nodiscard]] std::optional<SetElementOptionalDouble>
      loadSetElementOptionalDoubleJSON(std::string_view fileName);
    [[nodiscard]] int saveSetElementOptionalDoubleJSON(const SetElementOptionalDouble & element,
                                                       std::string_view fileName);

    [[nodiscard]] std::optional<SetElementEnum> loadSetElementEnumJSON(std::string_view fileName);
    [[nodiscard]] int saveSetElementEnumJSON(const SetElementEnum & element, std::string_view fileName);
}   // namespace Helper
