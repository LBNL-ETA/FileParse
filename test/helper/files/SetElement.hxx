#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct SetElementDouble;
    struct SetElementOptionalDouble;
    struct SetElementEnum;

    // XML functions
    [[nodiscard]] std::optional<SetElementDouble> loadSetElementDoubleXML(std::string_view fileName);
    [[nodiscard]] int saveSetElementDoubleXML(const SetElementDouble & element,
                                              std::string_view fileName);

    [[nodiscard]] std::optional<SetElementOptionalDouble>
      loadSetElementOptionalDoubleXML(std::string_view fileName);
    [[nodiscard]] int saveSetElementOptionalDoubleXML(const SetElementOptionalDouble & element,
                                                      std::string_view fileName);

    [[nodiscard]] std::optional<SetElementEnum> loadSetElementEnumXML(std::string_view fileName);
    [[nodiscard]] int saveSetElementEnumXML(const SetElementEnum & element, std::string_view fileName);

    // JSON functions
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
