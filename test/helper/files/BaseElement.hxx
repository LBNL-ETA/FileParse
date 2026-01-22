#pragma once

#include <string>
#include <optional>

namespace Helper
{
    struct BaseElement;

    // XML functions
    [[nodiscard]] std::optional<BaseElement> loadBaseElementXML(std::string_view fileName);
    [[nodiscard]] int saveBaseElementXML(const BaseElement & base, std::string_view fileName);

    // JSON functions
    [[nodiscard]] std::optional<BaseElement> loadBaseElementJSON(std::string_view fileName);
    [[nodiscard]] int saveBaseElementJSON(const BaseElement & base, std::string_view fileName);
}   // namespace Helper
